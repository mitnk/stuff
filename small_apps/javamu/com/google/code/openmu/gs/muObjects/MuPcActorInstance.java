package com.google.code.openmu.gs.muObjects;

import com.google.code.openmu.gs.serverPackets.ServerBasePacket;

/**
 * test class actor for pc instances to test interactivings betwens players
 * 
 * @author Miki
 */
public class MuPcActorInstance extends MuPcInstance {

	@Override
	public void sendPacket(ServerBasePacket packet) {
		System.out.println("Try send packet from actor :");
		System.out.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
		System.out.println(packet.getType());
		System.out.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
	}

	@Override
	public MuCharacterWear GetWearLook() {
		return new MuCharacterWear();
	}

}
