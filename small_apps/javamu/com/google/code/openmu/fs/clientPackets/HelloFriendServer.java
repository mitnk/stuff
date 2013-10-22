/*
 * To change this template, choose Tools ,(byte)0x Templates
 * and open the template in the editor.
 */

package com.google.code.openmu.fs.clientPackets;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

import com.google.code.openmu.gs.clientPackage.ClientBasePacket;
import com.google.code.openmu.fs.FriendTheard;

import com.google.code.openmu.fs.serverPackets.FriendHelloAnsfer;

/**
 * 
 * @author Miki i Linka
 */
public class HelloFriendServer extends ClientBasePacket {

	public HelloFriendServer(byte[] decrypt, FriendTheard _fs) {
		super(decrypt);
		int _IdRoom = decrypt[2] & 0xff;
		_IdRoom |= _decrypt[3] << 8 & 0xff00;
		Dec3bit(4, 10);
		final String Nick = readS(4, 10);
		System.out.println("Request to connect to Chat Room Id:" + _IdRoom
				+ " From Nick" + Nick);
		try {

			// _fs.getConnection().sendPacket(new byte[]{(byte) 0xc2, (byte)
			// 0x00, (byte) 0x1e, (byte) 0x02, (byte) 0xcc, (byte) 0xcc, (byte)
			// 0x02, (byte) 0xcc, (byte) 0x00, (byte) 0x41, (byte) 0x6D, (byte)
			// 0x65, (byte) 0x6C, (byte) 0x69, (byte) 0x73, (byte) 0x73, (byte)
			// 0x61, (byte) 0x6E, (byte) 0x61, (byte) 0x01, (byte) 0x41, (byte)
			// 0x6D, (byte) 0x65, (byte) 0x6C, (byte) 0x65, (byte) 0x6B, (byte)
			// 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00});
			_fs.getConnection().sendPacket(new FriendHelloAnsfer("System"));
		} catch (final IOException ex) {
			Logger.getLogger(HelloFriendServer.class.getName()).log(
					Level.SEVERE, null, ex);
		} catch (final Throwable ex) {
			Logger.getLogger(HelloFriendServer.class.getName()).log(
					Level.SEVERE, null, ex);
		}

	}

	@Override
	public String getType() {
		return " Hello to FS";
	}

}
