# cdt2hh - Plebble wallet plugin
Role-to-Role protocol for talent hunters and job seekers

The jobseeker would query for available jobs to the head hunter.
The candidate, who is running his wallet backend with the cdt role, would use her mobile to communicate with it, starting a trade with the cracked devs node using a bookmark or a QR Code
Both wallets would play the cdt2hh protocol resulting in a list of job offers visible to the candidate, with the possibility to directly apply for the job (this is a future improvement, so the apply button is not functional).
In the process, the hh node would obtain the data by querying the web2 crackeddevs api before delivering it to the candidate node.

A ready-to-go app can be found in the Google App-store. Find the app KATLASNET, install it and straight forward the app will contact my node and produce a custodial wallet backend for you with the cdt2hh protocol enabled. A bookmark to the crackeddevs service is also available to start interacting without any burdening preamble, that's web3!.


##directory cdt2hh/
  contains the backend code for the production of the libraries:
*libtrader-cdt2hh-cdt.so  	plugin for the candidate wallet
*libtrader-cdt2hh-hh.so		plugin for the head hunter role

  Build:
  clone the plebble codebase at https://github.com/root1m3/plebble

  Symlink this directory in the in us/core2/us/trader/ 
  bin/configure
  make

  Place each library in each corresponding running node at dir /home/gov/.plebble/wallet/trader/lib
  Restart the wallet backend: sysctl restart plebble-wallet


##directory poc_nodes/
    Contains wallet configurations for specific instances of the r2r (role-2-role) protocol
    ./deploy crackeddevs 
    		configures the wallet plugin in the hh wallet that I run as part of the demo
		The QR code for accessing the service by candidates is in the crackeddevs/env file

##directory poc_nodes/crackeddevs/
    Customization for a particular head-hunter organization running the role hh
    This is a demo, but in a real scenario this directory is supposed to be private for the organization crackeddevs
    Contains art, bitmaps, personality secret keys and a API key to externalize queries

##directory android
    symlink the front-end files for the android rpc-client found in this directory at the plebble codebase at us/core0/android/app/src/main/java/us/cash/

    Build, go to plebble codebase:
    cd core0/us
    make android
    cd android
    bin/sign_apk 
    Produces the android APK file.
    
