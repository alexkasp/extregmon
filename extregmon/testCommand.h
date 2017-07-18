#pragma once
#include "ICommand.h"
#include <vector>

class testCommand :
	public ICommand
{
	string STARTPACKETSIGNATURE1 = "bytes to udp/";
	string STARTPACKETSIGNATURE2 = "bytes from udp/";
	string STARTPACKETSIGNATURE3 = "bytes to tcp/";
	string STARTPACKETSIGNATURE4 = "bytes from tcp/";

	void DnsError(std::ifstream& log, std::string login, std::vector<string>& pt);
	/*
	solve config problem
	3558828a-6ac6-11e7-a446-0177bd11a386 Dialplan: sofia/internal/148695@sip.zadarma.com Regex (PASS) [14869540793] ${channel_name}(sofia/internal/148695@sip.zadarma.com) =~ /sofia/internal/148695@/ break=on-false
	3558828a-6ac6-11e7-a446-0177bd11a386 Dialplan: sofia/internal/148695@sip.zadarma.com Action record_session(/home/records/out_${strftime(%Y%m%d_%H%M%S)}_${caller_id_number}_${destination_number}.wav)
	
	   a=ptime:20
	      ------------------------------------------------------------------------
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] sofia.c:6760 Channel sofia/internal/148695@sip.zadarma.com entering state [early][183]
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] switch_core_media_bug.c:828 Attaching BUG to sofia/internal/148695@sip.zadarma.com
	      3558828a-6ac6-11e7-a446-0177bd11a386 EXECUTE sofia/internal/148695@sip.zadarma.com bridge({absolute_codec_string=PCMA}sofia/gateway/14869540793/74996478898)
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] switch_channel.c:1247 sofia/internal/148695@sip.zadarma.com EXPORTING[export_vars] [RFC2822_DATE]=[Mon, 17 Jul 2017 11:01:58 +0300] to event
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] switch_ivr_originate.c:2128 Parsing global variables
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [ERR] mod_sofia.c:4460 Invalid Gateway 14869540793
	      355f6fa0-6ac6-11e7-a453-0177bd11a386 2017-07-17 11:01:58.942561 [NOTICE] mod_sofia.c:4875 Close Channel N/A [CS_NEW]
	      355f6fa0-6ac6-11e7-a453-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] switch_core_state_machine.c:630 () Running State Change CS_DESTROY
	      355f6fa0-6ac6-11e7-a453-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] switch_core_state_machine.c:640 (N/A) State DESTROY
	      355f6fa0-6ac6-11e7-a453-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] mod_sofia.c:341 N/A SOFIA DESTROY
	      355f6fa0-6ac6-11e7-a453-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] switch_core_state_machine.c:640 (N/A) State DESTROY going to sleep
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [NOTICE] switch_ivr_originate.c:2763 Cannot create outgoing channel of type [sofia] cause: [INVALID_GATEWAY]
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] switch_ivr_originate.c:3751 Originate Resulted in Error Cause: 608 [INVALID_GATEWAY]
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [INFO] mod_dptools.c:3379 Originate Failed.  Cause: INVALID_GATEWAY
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [NOTICE] switch_channel.c:4804 Hangup sofia/internal/148695@sip.zadarma.com [CS_EXECUTE] [INVALID_GATEWAY]
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] switch_core_session.c:2796 sofia/internal/148695@sip.zadarma.com skip receive message [APPLICATION_EXEC_COMPLETE] (channel is hungup already)
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] switch_core_state_machine.c:539 (sofia/internal/148695@sip.zadarma.com) State EXECUTE going to sleep
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] switch_core_state_machine.c:473 (sofia/internal/148695@sip.zadarma.com) Running State Change CS_HANGUP
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.942561 [DEBUG] switch_ivr_async.c:1305 Stop recording file /home/records/out_20170717_110158_148695_74996478898.wav
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.962564 [DEBUG] switch_ivr_async.c:1366 Channel is hung up
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.962564 [DEBUG] switch_core_media_bug.c:1118 Removing BUG from sofia/internal/148695@sip.zadarma.com
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.962564 [DEBUG] switch_core_state_machine.c:739 (sofia/internal/148695@sip.zadarma.com) Callstate Change EARLY -> HANGUP
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.962564 [DEBUG] switch_core_state_machine.c:741 (sofia/internal/148695@sip.zadarma.com) State HANGUP
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.962564 [DEBUG] mod_sofia.c:431 Channel sofia/internal/148695@sip.zadarma.com hanging up, cause: INVALID_GATEWAY
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.962564 [DEBUG] mod_sofia.c:568 Responding to INVITE with: 484
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.962564 [DEBUG] switch_core_state_machine.c:60 sofia/internal/148695@sip.zadarma.com Standard HANGUP, cause: INVALID_GATEWAY
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.962564 [DEBUG] switch_core_state_machine.c:741 (sofia/internal/148695@sip.zadarma.com) State HANGUP going to sleep
	      3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.962564 [DEBUG] switch_core_state_machine.c:508 (sofia/internal/148695@sip.zadarma.com) State Change CS_HANGUP -> CS_REPORTING
	      send 836 bytes to udp/[212.193.100.168]:5060 at 11:01:58.970927:
	         ------------------------------------------------------------------------
	            SIP/2.0 484 Address Incomplete3558828a-6ac6-11e7-a446-0177bd11a386 2017-07-17 11:01:58.962564 [DEBUG] switch_core_state_machine.c:473 (sofia/internal/148695@sip.zadarma.com) Running State Change CS_REPORTING
	            
	            
	*/

public:
	testCommand();
	virtual ~testCommand();
	// check if line exists on server and find out status of registration
	virtual std::string getLineStatusCMD(std::string login);

	virtual bool checkSipPacketBegin(std::string line);
	virtual bool checkSipPacketEnd(std::string line);

	virtual std::string SayHello();
	virtual std::string getLogFilename();
	virtual std::string formateDateTime(std::tm tm);
	virtual void scanErrorInLog(std::ifstream& log, std::string login,std::vector<string>& pt);
	virtual std::string getTimeFromPacketBegin(std::string);
};

