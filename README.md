# Goldcoders's build of DWM for Huawei Matebook 13

## Patches
- Systray
- Pertag
- Center Float Window
- Cool Auto-start script (fixes background task taking too long for it to reboot or shutdown)
## Layouts
- Title
- BottomStack
- Spiral
- Dwindle
- Deck
- Monocle
- Centeredmaster
- CenteredFloating Master
## Custom Keybinding For Huawei Matebook 13
- Required Huawei WMI 
- Required Custom Scripts
## Custom Touchpad Gesture
- Required Fusuma
## Clipboard Manager
- Required Clipmenu

![pic-full-200822-0925-36](https://user-images.githubusercontent.com/55337687/90945764-90c0d400-e459-11ea-984c-9cdffab80493.png)

## Hybrid Graphics Intel + MX 150 Set Up

### Tested On Dota 2 Vulkan, Prior Vulkan 50+fps , With Nvidia Vulkan Enabled 150+ fps

> Xorg packages For Intel and Mesa
```
xf86-video-intel
xf86-video-vesa
```

- I remove nouveau package since im using nvidia ( and its better on performance)

> Nvidia Packages

```
nvidia
nvidia-prime
```

> Hybrid Mode uses `nvidia-prime` allows us to use prime-run (on demand GPU max 60fps)


- Add this Pacman Hook , Auto Update Nvidia Modules

/etc/pacman.d/hooks/nvidia.hook
```
[Trigger]
Operation=Install
Operation=Upgrade
Operation=Remove
Type=Package
Target=nvidia
Target=linux
# Change the linux part above and in the Exec line if a different kernel is used

[Action]
Description=Update Nvidia module in initcpio
Depends=mkinitcpio
When=PostTransaction
NeedsTargets
Exec=/bin/sh -c 'while read -r trg; do case $trg in linux) exit 0; esac; done; /usr/bin/mkinitcpio -P'
```

> Install vulkan packages
```
vulkan-intel
vulkan-tools
gpu-viewer
```

and installed Optimus manager QT , it comes with optimus manager as dependency

```
optimus-manage-qt
bbswitch
lightdm
lightdm-webkit2-greeter
lightdm-webkit-theme-aether-git
```

> bbswitch is needed so we can switch GPU with optimus manager

- lightdm is needed to properly switch GPU

change greeter-session and user-session

```
sudo sed -i 's/^\(#?greeter\)-session\s*=\s*\(.*\)/greeter-session = lightdm-webkit2-greeter #\1/ #\2g' /etc/lightdm/lightdm.conf
sudo sed -i 's/^\(#?user\)-session\s*=\s*\(.*\)/user-session = dwm #\1/ #\2g' /etc/lightdm/lightdm.conf
```

use aether theme
```
sudo sed -i 's/^webkit_theme\s*=\s*\(.*\)/webkit_theme = lightdm-webkit-theme-aether #\1/g' /etc/lightdm/lightdm-webkit2-greeter.conf
```

add your wallpaper 

```
cd /usr/share/lightdm-webkit/themes/lightdm-webkit-theme-aether/src/img/wallpapers
sudo wget url_to_wallpaper
sudo chmod 644 wallpaper.png
```

change avatar

```
cd /var/lib/AccountsService/icons
sudo wget https://avatars.dicebear.com/api/avataaars/sudoken.svg
sudo chmod 644 sudoken.svg
sudo mv sudoken.svg avatar.svg
sudo vim /var/lib/AccountsService/users/${whoami)
```

update /var/lib/AccountsService/users/${whoami)

```
[User]
Session=default
XSession=dwm
Icon=/var/lib/AccountsService/icons/sudoken.jpg
SystemAccount=false
```


any theme of lightdm will do, but ive installed aether.

this is my optimus.conf
/etc/optimus-manager/optimus-manager.conf

surprisingly all configuration for vulkan works out of the box 
same config for intel in arch wiki

```
[intel]
DRI=3
accel=
driver=modesetting
modeset=yes
tearfree=

[nvidia]
DPI=96
PAT=yes
allow_external_gpus=no
ignore_abi=no
modeset=yes
options=overclocking

[optimus]
auto_logout=no
pci_power_control=no
pci_remove=no
pci_reset=no
startup_auto_battery_mode=intel
startup_auto_extpower_mode=nvidia
startup_mode=intel
switching=bbswitch
```

my ~/.xinitrc

```
#!/usr/bin/env sh
. ~/.xprofile
ssh-agent dwm
```

my  config for lightdm

/etc/lightdm/lightdm conf
```
[LightDM]
run-directory=/run/lightdm

[Seat:*]
greeter-session=lightdm-webkit2-greeter
user-session=dwm
session-wrapper=/etc/lightdm/Xsession
```

config for lightdm-webkit2-greeter

```
[greeter]
debug_mode          = false
detect_theme_errors = true
screensaver_timeout = 300
secure_mode         = true
time_format         = LT
time_language       = auto
webkit_theme        = lightdm-webkit-theme-aether
[branding]
background_images = /usr/share/backgrounds
logo              = /usr/share/pixmaps/archlinux-logo.svg
user_image        = /usr/share/pixmaps/user.svg
```

ive only modified here is the user_image added image on that path.
and added 644 permission on that image or it wont show at all.

When I manually patched DWM , it doesnt come with dwm.desktop file

This  is needed so I can use it inside lightdm
this line is telling to use dwm as session
```
user-session=dwm
```

so to fix it ive added manually by creating a file

/usr/share/xsessions/dwm.desktop
```
[Desktop Entry]
Encoding=UTF-8
Name=Dwm
Comment=Dynamic window manager
Exec=dwm
Icon=dwm
Type=XSession
```

i do have  this lightdm config installed by optimus manager

/etc/lightdm/lightdm.conf.d/20-optimus-manager.conf 

So this basically is the one responsible for switching the Cards during login and logout
```
[Seat:*]
# Force using X
type=local
display-setup-script=/sbin/prime-offload
display-stopped-script=/sbin/prime-switch
```


Another thing to Add either on your .zshrc or .bashrc
This is needed for vulkan to reference proper GPU like intel and NVIDIA

```
export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/intel_icd.x86_64.json:/usr/share/vulkan/icd.d/nvidia_icd.json
```

to check vulkan is working run 

vulkaninfo

For MAX FPS use NVIDIA Mode By Setting it as Default Video Card On Startup









