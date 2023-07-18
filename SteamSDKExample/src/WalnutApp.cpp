#pragma comment(lib, "steam_api.lib")
#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "../steam/steam_api.h"
#include "Walnut/Image.h"

class CLobbyCreated_t
{
public:
    CLobbyCreated_t()
    {
        m_callResultLobbyCreated.Set(
            NULL,
            this,
            &CLobbyCreated_t::OnLobbyCreated);
    }

    void Set(SteamAPICall_t hSteamAPICall)
    {
        m_callResultLobbyCreated.Set(
            hSteamAPICall,
            this,
            &CLobbyCreated_t::OnLobbyCreated);
    }

    void OnLobbyCreated(LobbyCreated_t* pLobbyCreated, bool bIOFailure)
    {
        if (pLobbyCreated->m_eResult == k_EResultOK)
            printf("Lobby created successfully with SteamID: %llu\n", pLobbyCreated->m_ulSteamIDLobby);
        else
            printf("Error creating lobby.\n");
    }

private:
    CCallResult<CLobbyCreated_t, LobbyCreated_t> m_callResultLobbyCreated;
};

class SteamLobby {
public:
    void createLobby() {
        if (SteamAPI_Init())
        {
            printf("Steam API initialized successfully.\n");

            // Create lobby
            SteamAPICall_t hSteamAPICall = SteamMatchmaking()->CreateLobby(k_ELobbyTypeFriendsOnly, 4);

            // Create callback for lobby creation result
            CLobbyCreated_t callResultLobbyCreated;
            callResultLobbyCreated.Set(hSteamAPICall);

            // Call the steam callback
            SteamAPI_RunCallbacks();

            SteamAPI_Shutdown();
        }
        else
        {
            printf("Error initializing Steam API.\n");
        }
    }

    std::vector<std::string> getFriendsList() {
        std::vector<std::string> friends;
        if (SteamAPI_Init())
        {
            int friendCount = SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);
            for (int i = 0; i < friendCount; i++)
            {
                CSteamID friendSteamID = SteamFriends()->GetFriendByIndex(i, k_EFriendFlagImmediate);
                const char* friendName = SteamFriends()->GetFriendPersonaName(friendSteamID);
                friends.push_back(friendName);
            }
            SteamAPI_Shutdown();
        }
        return friends;
    }

    void joinLobby(CSteamID lobbySteamID) {
        if (SteamAPI_Init()) {
            printf("Steam API initialized successfully.\n");

            SteamMatchmaking()->JoinLobby(lobbySteamID);

            // Call the steam callback
            SteamAPI_RunCallbacks();

            SteamAPI_Shutdown();
        }
        else {
            printf("Error initializing Steam API.\n");
        }
    }
};


class ExampleLayer : public Walnut::Layer
{
public:
    ExampleLayer()
    {
        // we call this to let the steam client know we're going to be using its API
        if (SteamAPI_Init())
        m_Friends = m_SteamLobby.getFriendsList();
	}
    ~ExampleLayer()
    {
        // we call this to let the steam client know we're quitting so it can shutdown cleanly
		SteamAPI_Shutdown();
	}
    virtual void OnUIRender() override
    {
        ImGui::Begin("Hello");
        if (ImGui::Button("Create Lobby")) {
            m_SteamLobby.createLobby();
        }
        if (ImGui::Button("Join Lobby")) {
            m_IsJoinLobbyWindowOpen = true;
        }
        ImGui::End();

        ImGui::Begin("Friends");
        for (const auto& friendName : m_Friends)
        {
            ImGui::Text("%s", friendName.c_str());
        }
        ImGui::End();

        if (m_IsJoinLobbyWindowOpen) {
            ImGui::Begin("Join Lobby", &m_IsJoinLobbyWindowOpen);
            static char lobbyID[64] = "";
            if (ImGui::InputText("Lobby ID", lobbyID, IM_ARRAYSIZE(lobbyID), ImGuiInputTextFlags_EnterReturnsTrue)) {
                m_SteamLobby.joinLobby(CSteamID(std::stoull(lobbyID)));
            }
            ImGui::End();
        }
        // Process Steam callbacks
        SteamAPI_RunCallbacks();
    }
private:
    bool m_IsJoinLobbyWindowOpen = false;
    SteamLobby m_SteamLobby;
    std::vector<std::string> m_Friends;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
    Walnut::ApplicationSpecification spec;
    spec.Name = "SteamSDK Example";

    Walnut::Application* app = new Walnut::Application(spec);
    app->PushLayer<ExampleLayer>();
    return app;
}
