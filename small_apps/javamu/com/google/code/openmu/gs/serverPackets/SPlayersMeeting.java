/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.google.code.openmu.gs.serverPackets;

import java.io.IOException;
import java.util.ArrayList;

import com.google.code.openmu.gs.muObjects.MuObject;
import com.google.code.openmu.gs.muObjects.MuPcInstance;

/**
 * 
 * @author Miki i Linka
 */
public class SPlayersMeeting extends ServerBasePacket {

	private class SPlayerSubMiting extends ServerBasePacket {

		private final MuPcInstance player;
		public static final int SubSize = 34;

		public SPlayerSubMiting(MuPcInstance p) {
			player = p;
		}

		@Override
		public byte[] getContent() throws IOException, Throwable {
			writeC(0x00);
			writeC(player.getObjectId()); // ObjID, int
			writeC(player.getX()); // new X coordinate
			writeC(player.getY()); // new Y coodrinate
			writeC(player.getClas()); // 4 bits class, 4 bits how to spawn
										// (stand = 0x00)
			writeB(player.GetWearLook().getBytes()); // look ofcharacter
			writeC(0x00); // unknown
			writeC(0x00);// magic effect
			writeC(player.getAura().toByte()); // aura
			writeNick(player.getName());
			writeC(player.getOldX()); // original X coordinate
			writeC(player.getOldY()); // original Y coordinate
			writeC(player.getDirection() * 16 + player.getMurderStatus()); // 4
																			// bits
																			// direction
																			// |
																			// 4bits
																			// murderer
																			// status
			// murder status = (0x00 - green status, 0x01 - 1st hero, 0x02 - 2nd
			// hero, 0x03 - commoner)
			writeC(0x00); // unknown
			return getBytes();
		}

		@Override
		public String getType() {
			return "playersmeting sub";
		}

		@Override
		public boolean testMe() {
			return true;
		}
	}

	private final ArrayList<MuObject> _newPc;

	public SPlayersMeeting(ArrayList<MuObject> newPc) {
		_newPc = newPc;
	}

	@Override
	public byte[] getContent() throws IOException, Throwable {
		final int size = 5 + (_newPc.size() * SPlayerSubMiting.SubSize);
		mC2Header(0x12, size);
		writeC(_newPc.size());
		SPlayerSubMiting t;
		for (int i = 0; i < _newPc.size(); i++) {
			final MuPcInstance muObject = (MuPcInstance) _newPc.get(i);
			t = new SPlayerSubMiting(muObject);
			writeB(t.getContent());
		}
		return getBytes();
	}

	@Override
	public String getType() {
		return "pc Miting";
	}

	@Override
	public boolean testMe() {
		return true;
	}
}
