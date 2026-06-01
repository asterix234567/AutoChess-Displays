# ♟️ AutoChess

An automated, smart chessboard that brings the digital game into the physical world.

---

## 📝 Project Overview

**AutoChess** is a physical chessboard featuring self-moving figures that players can control via **TouchDisplay**. 
This Repo contains the PlatformIO-Project for the JC8048W550C Displays.  

The core mechanics are inspired by **3D printer motion systems** (CoreXY/Cartesian) and the structural components are predominantly **3D printed**. Our goal is to make this project entirely **Open Source**, with plans to release a comprehensive build guide in the future.

---

## 👥 The Team

We are a team of **three students** currently in our 3rd year at the **HTL Bulme** (Graz-Gösting, Austria). Driven by a passion for robotics, 3D printing, and software development, we are combining our skills to bring this interactive chess experience to life.

---

## 🚀 Sponsoring & Outreach

At the end of the school year, this project will be showcased in a **major presentation in front of the entire school**. 

### Why Sponsor Us?
* **Targeted Audience:** The event will be attended by hundreds of tech-savvy students, teachers, and makers who are highly interested in 3D printing, engineering, and electronics.
* **Direct Promotion:** While we currently do not maintain a massive social media presence, this presentation puts your brand directly in front of *exactly the right niche audience*.
* **Sponsor Visibility:** We offer prominent logo placement on the physical device, within the presentation slides, and inside this repository.

*Are you interested in supporting the future of open-source hardware? Feel free to reach out to us!*

---

## 📺 Display Setup & Hardware Integration

For the user interface and visual feedback, we are utilizing the **JC8048W550C** smart display module from Guition (available on [AliExpress](https://de.aliexpress.com/item/1005011859633796.html)).

### Technical Stack
* **Graphics Library:** [LVGL (Light and Versatile Graphics Library)](https://lvgl.io/)
* **Display Driver Library:** `esp32_smartdisplays`
* **Development Environment:** PlatformIO (VS Code)

---

### 🛠️ Troubleshooting & Known PlatformIO Issues

During the integration of the display libraries within PlatformIO, we encountered several configuration and compatibility hurdles. Below is our documentation on how we resolved them:

#### 1. Library Detection Bug (`esp32_smartdisplays`)
* **Issue:** Even though the `esp32_smartdisplays` library was correctly installed and located in the proper directory, PlatformIO initially failed to detect it.
* **Solution:** A simple restart of Visual Studio Code forced PlatformIO to re-index the workspace and successfully recognize the library dependencies.

#### 2. LVGL Version Incompatibility
* **Issue:** Upgrading LVGL beyond version `9.2.0` broke the build process. The compiler threw errors stating that `display->sw_rotate` is no longer available in newer versions.
* **Solution:** We strictly locked the LVGL library version to `9.2.0` (or below) in our `platformio.ini` configuration to maintain compatibility with the display driver framework.

#### 3. Missing `GPIO_BLCK` Definition in Sunton Boards
* **Issue:** The board definitions provided by the `platformio-espressif32-sunton` submodule were faulty. Compiling resulted in errors because the backlight control pin (`GPIO_BLCK`) was undefined. 
* **Discovery:** We noticed that the repository *clocky* had a functioning implementation where this definition was present.

#### 4. Solution: Custom Board Definition (`myboards`)
To circumvent the buggy submodule definitions, we created a custom configuration:
* We created a dedicated directory named `myboards` in our project root.
* Inside, we took the original definition of the `JC8048S050C` board, renamed it to `JC8048W550C`, and corrected the pin mappings (ensuring `GPIO_BLCK` is properly defined).
* *Tip:* If you need to include or create custom boards in PlatformIO yourself, you can read the official guide here: [PlatformIO Custom Board Creation](https://docs.platformio.org/en/latest/platforms/creating_board.html).
