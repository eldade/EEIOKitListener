# EEIOKitListener
Obtain battery and power information on iOS using IOKit.

This is a sample program that uses `IOKit` on iOS to obtain battery and charging information for iOS devices. It can also be looked at as a simple example program on how to use `IOKit` on iOS.

> This code is not suitable for App Store usage and will very likely be rejected by Apple due to the use of `IOKit`, which is considered a private API on iOS.

## Sample Power Data

Here is a sample dictionary demonstrating the type of information exposed by this code. The actual contents of the dictionary varies by iOS version. On iOS versions 7-9 the dictionary is quite detailed, but its contents were significantly curtailed in iOS 10 (to the point where it is of little value).

```
{
    AdapterDetails =     {
        Amperage = 1000;
        Description = "usb host";
        FamilyCode = "-536854528";
        PMUConfiguration = 1000;
        Watts = 5;
    };
    AdapterInfo = 16384;
    Amperage = 1000;
    AppleRawCurrentCapacity = 1279;
    AppleRawMaxCapacity = 1275;
    AtCriticalLevel = 0;
    AtWarnLevel = 0;
    BatteryData =     {
        BatterySerialNumber = REDACTED;
        ChemID = 355;
        CycleCount = 524;
        DesignCapacity = 1420;
        Flags = 640;
        FullAvailableCapacity = 1325;
        ManufactureDate = REDACTED;
        MaxCapacity = 1273;
        MfgData = REDACTED;
        QmaxCell0 = 1350;
        StateOfCharge = 100;
        Voltage = 4194;
    };
    BatteryInstalled = 1;
    BatteryKey = "0003-default";
    BootBBCapacity = 52;
    BootCapacityEstimate = 2;
    BootVoltage = 3518;
    CFBundleIdentifier = "com.apple.driver.AppleD1815PMU";
    ChargerConfiguration = 990;
    CurrentCapacity = 1275;
    CycleCount = 524;
    DesignCapacity = 1420;
    ExternalChargeCapable = 1;
    ExternalConnected = 1;
    FullyCharged = 1;
    IOClass = AppleD1815PMUPowerSource;
    IOFunctionParent64000000 = <>;
    IOGeneralInterest = "IOCommand is not serializable";
    IOInterruptControllers =     (
        IOInterruptController34000000,
        IOInterruptController34000000,
        IOInterruptController34000000,
        IOInterruptController34000000
    );
    IOInterruptSpecifiers =     (
        <03000000>,
        <26000000>,
        <04000000>,
        <24000000>
    );
    IOMatchCategory = AppleD1815PMUPowerSource;
    IOPowerManagement =     {
        CurrentPowerState = 2;
        DevicePowerState = 2;
        MaxPowerState = 2;
    };
    IOProbeScore = 0;
    IOProviderClass = AppleD1815PMU;
    InstantAmperage = 0;
    IsCharging = 0;
    Location = 0;
    Manufacturer = A;
    MaxCapacity = 1275;
    Model = "0003-A";
    Serial = REDACTED;
    Temperature = 2590;
    TimeRemaining = 0;
    UpdateTime = 1461830702;
    Voltage = 4182;
    "battery-data" =     {
        "0003-default" = <...>;
        "0004-default" = <...>;
        "0005-default" = <...};
    "built-in" = 1;
}
```
