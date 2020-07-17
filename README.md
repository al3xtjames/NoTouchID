# NoTouchID
[Lilu][1] plugin for disabling Touch ID support.

BiometricKit.framework in 10.13.4+ assumes a Touch ID sensor is present when a compatible board ID
is used, which causes lag in authentication dialogs (as well as a delayed login screen). Patching
this out resolves such hangs.

### Configuration
 - Add `-nobiooff` to disable NoTouchID
 - Add `-nobiobeta` to enable NoTouchID on unsupported OS versions (10.13-10.16 are supported by
   default)

### Downloads
Available on the [releases][2] page.

[1]: https://github.com/acidanthera/Lilu
[2]: https://github.com/al3xtjames/NoTouchID/releases
