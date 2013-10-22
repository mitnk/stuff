/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.google.code.openmu.fs.serverPackets;

import java.io.IOException;
import java.util.Vector;

import com.google.code.openmu.gs.serverPackets.ServerBasePacket;


/**
 * 
 * @author Miki i Linka
 */
public class FriendHelloAnsfer extends ServerBasePacket {

	private final Vector<String> _nicks = new Vector();

	/**
	 * add single nick
	 * 
	 * @param nick
	 */
	public FriendHelloAnsfer(String nick) {
		_nicks.add(nick);
	}

	/**
	 * with multi nicks
	 * 
	 * @param nickv
	 */
	public FriendHelloAnsfer(Vector<String> nickv) {
		_nicks.addAll(nickv);
	}

	@Override
	public byte[] getContent() throws IOException, Throwable {
		final int size = (11 * (_nicks.size())) + 8;
		mC2Header(0x02, size);
		writeC(0xcc); // unk 0xcc
		writeC(0xcc); // unk 0xcc
		writeC(_nicks.size()); // count of subs
		writeC(0xcc); // unk 0xcc
		for (int i = 0; i < _nicks.size(); i++) {
			makeSub(_nicks.get(i), i); // put subs
		}

		return getBytes();
	}

	public void makeSub(String nick, int pos) {
		writeC(pos); // put position of list
		writeNick(nick);// put name flipped 0x00 to 10 bytes
	}

	@Override
	public String getType() {
		return "Friend hello ansfer";
	}

	@Override
	public boolean testMe() {
		return true;
	}
}
