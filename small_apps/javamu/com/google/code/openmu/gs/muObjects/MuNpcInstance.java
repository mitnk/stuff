package com.google.code.openmu.gs.muObjects;

import com.google.code.openmu.gs.templates.MuNpc;
import com.google.code.openmu.gs.templates.MuWeapon;

public class MuNpcInstance extends MuCharacter {
	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.google.code.openmu.gs.muObjects.MuCharacter#startAttack(com.google.code.openmu
	 * .gs.muObjects.MuCharacter)
	 */

	@Override
	public void startAttack(MuCharacter target) {
		super.startAttack(target);
	}

	public MuNpcInstance(MuNpc temp) {
		_npcTemplate = temp;
		_objectType = 1;
		setName(temp.getName());

	}

	private boolean _isAtackable;
	private MuNpc _npcTemplate;

	/**
	 * set weward exp when die
	 * 
	 * @param i
	 *            exp
	 */
	public void setExpReward(int i) {
	}

	/**
	 * @return reward exp for die a
	 */
	public int getExpReward() {
		return 10;// _expReward;
	}

	/**
	 * @return zwraca id moba/mpc
	 */
	public int getNpcId() {
		return _npcTemplate.getNpcId();
	}

	/**
	 * @return czy mozna go atakowac
	 */
	public boolean isAtackable() {
		return _isAtackable;
	}

	/**
	 * ustawia flage czy mozna go atakowac
	 * 
	 * @param b
	 *            flaga
	 */
	public void setAtackable(boolean b) {
		_isAtackable = b;
	}

	/**
	 * @return bazowe statystyki npc
	 */
	public MuNpc getNpcTemplate() {
		return _npcTemplate;
	}

	/**
	 * ustawia npctemplae
	 * 
	 * @param npcTemplate
	 */
	public void setNpcTemplate(MuNpc npcTemplate) {
		_npcTemplate = npcTemplate;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.google.code.openmu.gs.muObjects.MuCharacter#getActiveWeapon()
	 */
	@Override
	public MuWeapon getActiveWeapon() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	/**
	 * get name from npc teplate 
	 */
	public String getName() {
		return _npcTemplate.getName();
	}

	@Override
	public void moveTo(int x, int y) {
		super.moveTo(x, y);
	}

	@Override
	public void updateKnownsLists() {
		super.updateKnownsLists();

	}
}
