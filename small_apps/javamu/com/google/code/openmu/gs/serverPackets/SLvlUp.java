/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.google.code.openmu.gs.serverPackets;

import java.io.IOException;

import com.google.code.openmu.gs.muObjects.MuPcInstance;

/**
 * 
 * @author Miki i Linka
 */
public class SLvlUp extends ServerBasePacket {

	int Level;
	int LevelUpPoint;
	int MaxLife;
	int MaxMana;
	int MaxBP;
	int AddPoint;
	int MaxAddPoint;

	public SLvlUp(MuPcInstance pc) {
		super();
		Level = pc.getLvl();
		LevelUpPoint = pc.getLp();
		MaxLife = pc.getMaxHp();
		MaxMana = pc.getMaxMp();
		MaxBP = pc.getMaxSp();
		AddPoint = 1; // ??
		MaxAddPoint = 1;// ??
	}

	@Override
	public byte[] getContent() throws IOException, Throwable {
		mC3Header(0xf3, 0x05, 0x12);
		writeI(Level);
		writeI(LevelUpPoint);
		writeI(MaxLife);
		writeI(MaxMana);
		writeI(MaxBP);
		writeI(AddPoint); // ?
		writeI(MaxAddPoint); // ?
		return getBytes();
	}

	@Override
	public String getType() {
		return "";
	}

	@Override
	public boolean testMe() {
		return true;
	}
}
