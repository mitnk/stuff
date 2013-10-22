package com.google.code.openmu.gs.clientPackage;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

import com.google.code.openmu.gs.ClientThread;
import com.google.code.openmu.gs.muObjects.MuPcInstance;
import com.google.code.openmu.gs.serverPackets.SInwentoryList;
import com.google.code.openmu.gs.serverPackets.SLiveStats;
import com.google.code.openmu.gs.serverPackets.SManaStaminaStats;
import com.google.code.openmu.gs.serverPackets.SSelectedCharacterEnterAnsfer;
import com.google.code.openmu.gs.serverPackets.SSkillList;


public class CA0Request extends ClientBasePacket {

	private MuPcInstance cha = null;
	private final SSelectedCharacterEnterAnsfer _characterStatsPack = new SSelectedCharacterEnterAnsfer();
	private final SSkillList _skilPack = new SSkillList();
	private final SManaStaminaStats _manaStaminaMaximalsPack = new SManaStaminaStats(
			SManaStaminaStats._UPDATE_MAX);
	private final SLiveStats _liveMaximalsPack = new SLiveStats(
			SLiveStats._UPDATE_MAX); // private byte[] _itemPack={(byte)
										// 0xc4,0x00,0x06,(byte)
										// 0xf3,0x10,0x00,0x//00};

	// private byte[] _a0ansferPack={(byte) 0xc1,0x05,(byte) 0xa0,0x01,(byte)
	// 0xaa,0x00};
	// private byte[] _learnSkill={(byte) 0xc1 ,0x08 ,(byte) 0xf3 ,0x11 ,(byte)
	// 0xfe ,0x01 ,0x04 ,0x00};
	public CA0Request(byte[] decrypt, ClientThread _client) {
		super(decrypt);
		cha = _client.getActiveChar();
		cha.setNetConnection(_client.getConnection());

		setCharacterStats();
		setSkillList();
		setManaStaminaMaximals();
		setLiveMaximals();

		try {
			_client.getConnection().sendPacket(
					new byte[] { (byte) 0xc1, (byte) 0x05, (byte) 0xa0,
							(byte) 0x01, (byte) 0xaa });
			_client.getConnection().sendPacket(_characterStatsPack);
			_client.getConnection().sendPacket(
					new SInwentoryList(_client.getActiveChar().getInventory()));
			_client.getConnection().sendPacket(_liveMaximalsPack);
			_client.getConnection().sendPacket(_manaStaminaMaximalsPack);

			// _client.getConnection().sendPacket(_itemPack);
			// _client.getConnection().sendPacket(_inwentoryPack);
			// _client.getConnection().sendPacket(_skilPack);
			// Must add it, even it if already exists, so meeting packets are
			// sent
			// Previously sent meeting packets are disregarded by the client
			_client.getActiveChar().getCurrentWorldRegion()
					.addObject(_client.getActiveChar());
			// _client.getConnection().sendPacket(_a0ansferPack);
			// _client.getConnection().sendPacket(_learnSkill);

		} catch (final IOException ex) {
			Logger.getLogger(CA0Request.class.getName()).log(Level.SEVERE,
					null, ex);
		} catch (final Throwable ex) {
			Logger.getLogger(CA0Request.class.getName()).log(Level.SEVERE,
					null, ex);

		}
	}

	private void setCharacterStats() {

		_characterStatsPack.setStatistic(cha.getStr(), cha.getAgi(),
				cha.getVit(), cha.getEne(), cha.getCom());
		_characterStatsPack.setExperance(cha.getExp(), cha.getExpOnNewLvl(),
				cha.getLp());
		_characterStatsPack.setPosicion(cha.getM(), cha.getX(), cha.getY(),
				cha.getStatus());
		_characterStatsPack.setZen(cha.getZen());
		System.out.println("Statystyki postaci zaladowane");
	}

	private void setLiveMaximals() {
		_liveMaximalsPack.setLive(cha.getMaxHp());

	}

	private void setManaStaminaMaximals() {

		_manaStaminaMaximalsPack.setMana(cha.getMaxMp());
		_manaStaminaMaximalsPack.setStamina(cha.getMaxSp());
	}

	private void setSkillList() {
		System.out.println("Skille postaci zaloadowane");

	}

	@Override
	public String getType() {

		return null;
	}
}
