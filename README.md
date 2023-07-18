# SteamSDKExample

This project is a simple example of how to use the Steamworks SDK for C++. It provides basic functionality for creating, joining, and managing Steam lobbies, as well as fetching the user's friends list. It utilizes the Walnut application template to quickly get started. You can check out the Walnut template [here](https://github.com/StudioCherno/WalnutAppTemplate).

## Features

The current code base includes the following features:

- [x] Steam API initialization and shutdown
- [x] Create Steam lobby
- [x] Join Steam lobby
- [x] Fetch and display Steam friends list
- [x] Steam callbacks handling
- [ ] Update Steam lobby
- [ ] Fetch Steam lobby data
- [ ] Kick/Ban from Steam lobby
- [ ] Set Steam lobby data
- [ ] Leave Steam lobby

## Usage

This project uses C++ and the Steamworks SDK. After you clone this repository and have the necessary dependencies installed, you can compile and run the project using your preferred C++ compiler and environment.

```cpp
Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
    Walnut::ApplicationSpecification spec;
    spec.Name = "SteamSDK Example";

    Walnut::Application* app = new Walnut::Application(spec);
    app->PushLayer<ExampleLayer>();
    return app;
}
```

This code snippet shows the main entry point of the application.

## Contributing

Contributions are welcome!

## License

This project is under the MIT license. See the [LICENSE](LICENSE.md) file for details.

For more questions, please feel free to ask.
