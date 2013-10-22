package com.google.code.openmu.gs.clientPackage;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

import com.google.code.openmu.gs.ClientThread;
import com.google.code.openmu.gs.serverPackets.SCharacterListAnsfer;


public class CCharacterListRequest extends ClientBasePacket {

	public CCharacterListRequest(byte[] decrypt, ClientThread cl)
			throws IOException {
		super(decrypt);
		try {
			if (cl.getChList().needRead()) {
				cl.readCharacterList();
			}
			cl.getConnection().sendPacket(
					new SCharacterListAnsfer(cl.getChList()));
		} catch (final Throwable ex) {
			Logger.getLogger(CCharacterListRequest.class.getName()).log(
					Level.SEVERE, null, ex);
		}
	}

	@Override
	public String getType() {
		return null;
	}

}
