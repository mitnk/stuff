/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.google.code.openmu.gs.clientPackage;

import com.google.code.openmu.gs.ClientThread;
import com.google.code.openmu.gs.muObjects.MuWorld;

/**
 * 
 * @author Miki i Linka
 */
public class CItemPickUpRequest extends ClientBasePacket {
	int id; // id wich item to get

	public CItemPickUpRequest(byte[] decrypt, ClientThread _client) {
		super(decrypt);
		// decrypt[1]=0x00 :// to fix with |0x80
		id = decrypt[2];
		// MuObject[] obj =
		// _client.getActiveChar().getCurrentWorldRegion().getVisibleObjects();
		// for (int i=0; i<obj.length; i++)
		// if (((MuObject)obj[i]).getObjectId() == id) {
		// ((MuObject)obj[i]).getCurrentWorldRegion();
		// MuWorld.getInstance().removeObject(obj[i]);
		// break;
		// }
		MuWorld.getInstance().removeObject(id);
		System.out.println("Request to pickup item id:" + id);
	}

	@Override
	public String getType() {
		return "pck up item";
	}
	// 0x22 opcode

}
