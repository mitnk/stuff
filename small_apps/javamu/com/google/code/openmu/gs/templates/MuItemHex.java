package com.google.code.openmu.gs.templates;

/**
 * klasa ma za zadanie danie podsawowegi interfejsu do zazadzaniem kodow
 * hexowych itemow
 * 
 * @author MikiOne, Marcel
 * @example hex itemu: c0 00 16 00 00 <br>
 * 
 */
public class MuItemHex implements MuItemOptBits, MuItemExeBits {

	private final byte[] _item = { 0, 0, 0, 0, 0 };

	/**
	 * Crtate new itemhhex from stats
	 * 
	 * @param index
	 * @param pos
	 * @param dur
	 *            durabilaty
	 * @param lvl
	 * @param opt
	 *            option
	 * @param eopt
	 *            exe option
	 * @param luck
	 *            is look?
	 * @param skill
	 *            is skill?
	 * @return new MuItemHex instance
	 */
	public static MuItemHex MakeItem(int index, int grup, int dur, int lvl,
			int opt, int eopt, boolean luck, boolean skill) {
		final MuItemHex i = new MuItemHex();
		i.setGroupAndIndex((byte) index, (byte) grup);
		i.setDurability((byte) dur);
		i.setLvl((byte) lvl);
		i.setOption((byte) opt);
		i.setExeOpt((byte) eopt);
		if (luck) {
			i.setLuck();
		}
		if (skill) {
			i.setSkill();
		}
		return i;
	}

	@Override
	public String toString() {
		int extra;
		if (isOpt_p16()) {
			extra = 16;
		} else {
			extra = getOption();
		}
		return "[GID:" + getGroup() + "]" + "[ID:" + getIndex() + "]" + "[Dur:"
				+ (getDurability() & 0xFF) + "]" + "[Lvl:" + getLvl() + "]"
				+ "[Opt:" + extra + "]" + "[L:" + isLuck() + "]" + "[S:"
				+ isSkill() + "]";
	}

	/**
	 * @return hex itemu
	 */
	public byte[] toByteArray() {
		return _item;
	}

	/**
	 * funkcja pobiera hex itemu z denego bufora t i ofsetu of
	 * 
	 * @param t
	 *            bufor zrudlowy
	 * @param of
	 *            offset w buforze
	 */
	public void fromByteArray(byte[] t, int of) {
		System.arraycopy(t, of, _item, 0, 5);

	}

	/**
	 * wstawia hex itemu do danego lancucha t na miejsce o ofsecie of
	 * 
	 * @param t
	 *            buffwhere put bits
	 * @param of
	 *            offset in buffor
	 */
	public void intoByteArray(byte[] t, int of) {
		System.arraycopy(_item, 0, t, of, 5);
	}

	/**
	 * clean hex items <br>
	 * rewrite it by 0x00
	 */
	public void clearHexItem() {
		_item[0] = 0;
		_item[1] = 0;
		_item[2] = 0;
		_item[3] = 0;
		_item[4] = 0;
	}

	public byte getGroup() {
		return (byte) ((_item[0] >> 4) & 0x0f);
	}

	public byte getIndex() {
		return (byte) (_item[0] & 0x0f);
	}

	public boolean setGroupAndIndex(byte GroupIndex, byte Index) {
		if ((GroupIndex > 0x0F) || (Index > 0x0F)) {
			return false;
		}
		byte t = GroupIndex;
		t = (byte) (t << 4);
		t |= Index;
		_item[0] = t;
		return true;
	}

	// /**
	// * pobiera lvl itemu z hexa
	// */
	// public void lvlFromHex() {
	// _lvl = (_item[2] >> 3) & 0x0f;
	// }
	//
	// /**
	// * stawial lvl itemu do hexa
	// */
	// public void lvlIntoHex() {
	// _item[2] = (byte) (_lvl << 3);
	// }
	/**
	 * wdurabilaty from hex u
	 */
	public byte getDurability() {
		return _item[2];
	}

	/**
	 * set durabilaty to hex
	 */
	public void setDurability(byte Durability) {
		_item[2] = Durability;
	}

	@Override
	public int getOption() {
		if ((_item[IT_BIT_OPT] & IT_OPTp4) == IT_OPTp4) {
			return 4;
		}
		if ((_item[IT_BIT_OPT] & IT_OPTp8) == IT_OPTp8) {
			return 8;
		}
		if ((_item[IT_BIT_OPT] & IT_OPTp12) == IT_OPTp12) {
			return 12;
		}
		return 0;
	}

	@Override
	public int getLvl() {
		return (_item[IT_BIT_OPT] >> 3) & 0x0f;
	}

	@Override
	public boolean isLuck() {
		return (_item[IT_BIT_OPT] & IT_LUCK) == IT_LUCK;
	}

	@Override
	public boolean isSkill() {
		return (_item[IT_BIT_OPT] & IT_SKILL) == IT_SKILL;
	}

	@Override
	public void setLuck() {
		_item[IT_BIT_OPT] = (byte) (_item[IT_BIT_OPT] | IT_LUCK);
	}

	@Override
	public void setSkill() {
		_item[IT_BIT_OPT] = (byte) (_item[IT_BIT_OPT] | IT_SKILL);
	}

	@Override
	public boolean isExeOpt1() {
		return (_item[IT_EXE_BIT] & EXEOPT1) == EXEOPT1;
	}

	@Override
	public boolean isExeOpt2() {
		return (_item[IT_EXE_BIT] & EXEOPT2) == EXEOPT2;
	}

	@Override
	public boolean isExeOpt3() {
		return (_item[IT_EXE_BIT] & EXEOPT3) == EXEOPT3;
	}

	@Override
	public boolean isExeOpt4() {
		return (_item[IT_EXE_BIT] & EXEOPT4) == EXEOPT4;
	}

	@Override
	public boolean isExeOpt5() {
		return (_item[IT_EXE_BIT] & EXEOPT5) == EXEOPT5;
	}

	@Override
	public boolean isExeOpt6() {
		return (_item[IT_EXE_BIT] & EXEOPT6) == EXEOPT6;
	}

	@Override
	public boolean isOpt_p16() {
		return (_item[IT_EXE_BIT] & IT_p16) == IT_p16;
	}

	@Override
	public boolean isLongId() {
		return (_item[IT_EXE_BIT] & IT_LONGID) == IT_LONGID;
	}

	@Override
	public void setExeOpt(byte ExcellentOption) {
		switch (ExcellentOption) {
		case 1:
			_item[IT_EXE_BIT] = (byte) (_item[IT_EXE_BIT] | EXEOPT1);
			return;
		case 2:
			_item[IT_EXE_BIT] = (byte) (_item[IT_EXE_BIT] | EXEOPT2);
			return;
		case 3:
			_item[IT_EXE_BIT] = (byte) (_item[IT_EXE_BIT] | EXEOPT3);
			return;
		case 4:
			_item[IT_EXE_BIT] = (byte) (_item[IT_EXE_BIT] | EXEOPT4);
			return;
		case 5:
			_item[IT_EXE_BIT] = (byte) (_item[IT_EXE_BIT] | EXEOPT5);
			return;
		case 6:
			_item[IT_EXE_BIT] = (byte) (_item[IT_EXE_BIT] | EXEOPT6);
			return;
		default:
			return;
		}
	}

	@Override
	public void setOpt_p16() {
		_item[IT_EXE_BIT] = (byte) (_item[IT_EXE_BIT] | IT_p16);
	}

	@Override
	public void setLongId() {
		_item[IT_EXE_BIT] = (byte) (_item[IT_EXE_BIT] | IT_LONGID);
	}

	@Override
	public void setOption(int opt) {
		switch (opt) {
		case 4:
			_item[IT_BIT_OPT] = (byte) (_item[IT_BIT_OPT] | IT_OPTp4);
			return;
		case 8:
			_item[IT_BIT_OPT] = (byte) (_item[IT_BIT_OPT] | IT_OPTp8);
			return;
		case 12:
			_item[IT_BIT_OPT] = (byte) (_item[IT_BIT_OPT] | IT_OPTp12);
			return;
		case 16:
			setOpt_p16();
			return;
		default:
			return;
		}
	}

	@Override
	public void setLvl(int lvl) {
		_item[IT_BIT_OPT] |= (lvl << 3);
	}
}
