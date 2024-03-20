
Build CSD2Test-ares app:

1. clone csd2 application:
git clone https://github.com/Prashant-Jagtap-einfochips/csd2Test-ares.git

2. Open Momentics IDE

3. Open Project:
	File -> Open Project from file system
	
4. right click on csd2Test-ares project and select 
	Build Configurations -> set active -> aarch64le-debug
	
5. right click on csd2Test-ares project and select 
	Clean project
	
6. right click on csd2Test-ares project and select 
	Build project
	
7. Inside Build->aarch64le-debug directory "CSD2Test" test app executable is generated

Verification of CSD2Test Application:

1. Push acdb files for module under test (e.g capi-gain-ctrl-ares) on device at /mnt/etc/acdb/adp_8295 (for SA8295)

2. Push .so files of control and data module at /mnt/etc/images/dsp

3. Push CSD2Test to /data 

4. change permisssion of CSD2Test to executable

5. Reset device

6. Connnect to the COM port of device and enter following commands
	- mq
	- audio_service -f /ifs/etc/lpass_cfg
	- mount -uw /mnt

7. Start Playback: >>audio_chime -g 21 <wav file path>

8. Verify that graph getting loaded in QACT tool (Use QACT Ver 8.0.33)

9. Run CSD2Test application 

10. Check that effects are getting applied (Also verify that parameter values getting updated in QACt tool)





