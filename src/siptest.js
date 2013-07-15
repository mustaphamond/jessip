// Test SIP script

sip.log("Welcome to Dave's test script");

sip.initialize();

sip.log('Setting up transports...');

sip.addTransport(
		{
			type: sip.transportType.tcp,
			ipVersion: sip.ipVersion.v4,
			port: 5065
		});

sip.addTransport(
		{
			type: sip.transportType.udp,
			ipVersion: sip.ipVersion.v4,
			port: 5065
		});

sip.log('Setting up handlers...');

function onKill(e)
{
	 sip.end();
}

function onAbandonedCallNotify(e)
{
	sip.log('Received abandoned call notify');
	var invite=sip.createInviteMessage('sip:911@172.20.136.111',
			{
				clientNewSession: function(e) { sip.log(e.message); e.sip.end(); },
				terminated: function(e) { sip.scheduleEvent(onKill); }
			});
	invite.from='sip:911@jessip';
	sip.sendMessage(invite);
}

sip.log('Running...');

sip.subscribeToEvent('sip:911@172.252.5.141','nena-AbandonedCall',
		{
			notify: onAbandonedCallNotify
		});

//sip.scheduleEvent(onAbandonedCallNotify);

sip.run();

