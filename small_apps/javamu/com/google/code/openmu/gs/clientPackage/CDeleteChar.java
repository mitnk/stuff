package com.google.code.openmu.gs.clientPackage;

import java.io.IOException;

import com.google.code.openmu.gs.ClientThread;
import com.google.code.openmu.gs.database.MuCharacterListDB;
import com.google.code.openmu.gs.serverPackets.SDeleteChar;


/**
 * 
 * @author Marcel , Mikione
 * 
 */
public class CDeleteChar extends ClientBasePacket {
	private final String _personalcode;
	private final String _name;

	public CDeleteChar(byte[] decrypt, ClientThread _client)
			throws IOException, Throwable {
		super(decrypt);
		String p_code = _client.getUser().getChCode();
		// TODO sometimes if its nathing set i DB there is null so w relace it
		// as ""
		if (p_code == null) {
			p_code = "";
		}
		int result = 0x02;
		_name = readS(2, 10);
		_personalcode = readS(12, 7);
		if (_personalcode.compareTo(p_code) == 0) {
			result = 0x01;
		}
		// if (_personalcode.length() != 7)
		// result = 0x02;
		if (_client.getChList().getChar(_name).isInGuild()) {
			result = 0x00;
		}
		if (result == 0x01) {
			_client.getChList().removeChar(_name);
			final MuCharacterListDB cdb = new MuCharacterListDB(_client
					.getUser().getId());
			cdb.removeCharacterFromDB(_name);
		}
		_client.getConnection().sendPacket(new SDeleteChar(_name, result));
	}

	@Override
	public String getType() {
		return null;
	}
}
