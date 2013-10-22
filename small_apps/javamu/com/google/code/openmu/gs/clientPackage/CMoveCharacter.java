package com.google.code.openmu.gs.clientPackage;

import com.google.code.openmu.gs.ClientThread;
import com.google.code.openmu.gs.muObjects.MuObject;
import com.google.code.openmu.gs.muObjects.MuPcInstance;

/*
 * TODO Source c++; to reimplement in java
 * truct MovePack
 {
 PMSG_HEADA _head;
 unsigned char PosX;
 unsigned char PosY;
 unsigned char MovePath[8];
 };

 char const stepDirections[16] = {-1, -1, 0, -1, 1, -1, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0};

 class CCharacterMove:public CBPacket {
 int step_count;
 int newx;
 int newy;

 public:
 CCharacterMove(HexBuff *b,MuClientTheard *t):CBPacket(b,t){};
 virtual ~CCharacterMove(){};
 void debuild()
 {

 MuPcInstance* activeChar = _cl->getActiveCharacter();

 unsigned char *cbuff= buff->getPointer();
 MovePack *p = (MovePack*)cbuff;
 unsigned char stepCount = p->MovePath[0] & 0x0F;
 if(stepCount <=15)
 {
 unsigned char dPosX = p->PosX;
 unsigned char dPosY= p->PosY;
 unsigned char HDirection = p->MovePath[0] >>4;
 short dStepDirection =0;
 if(stepCount >0)
 {
 stepCount++;
 };
 for (int i =1 ; i < stepCount; i++)
 {
 if ((i & 1) == 1 )
 {
 dStepDirection = p->MovePath[(i+1)>>1]>>4;
 }
 else
 {
 dStepDirection = p->MovePath[(i+1)>>1] & 0x0F;
 };
 dPosX += stepDirections[dStepDirection <<1];
 dPosY += stepDirections[(dStepDirection << 1)+1];
 };
 activeChar->setPosXY(p->PosX,p->PosY);
 activeChar->MoveTo(dPosX,dPosY);
 } else
 {
 std::cout << "Wrong Number of steps !!! \n" ;
 };

 */

public class CMoveCharacter extends ClientBasePacket {
    private static final short stepDirections[] = { -1, -1, 0, -1, 1, -1, 1, 0,
            1, 1, 0, 1, -1, 1, -1, 0 };

    private short _nX;
    private short _nY;

    public CMoveCharacter(byte[] data, ClientThread _client) {
        super(data);
        _nX = (short) (data[1] & 0xff);
        _nY = (short) (data[2] & 0xff);
        // System.out.println("Postac sie porusza na wsp :["+_nX+","+_nY+"].");
        final short stepCount = (short) (data[3] & 0x0F);
        if (stepCount <= 15) {
            final short headingDirection = (short) ((data[3] >> 4) & 0x0F); // where
                                                                            // char
                                                                            // will
                                                                            // head
                                                                            // after
                                                                            // completing
                                                                            // walk
            short stepDirection = 0;
            for (int i = 0; i < stepCount; i++) {
                if ((i & 1) == 0) {
                    stepDirection = (short) ((data[4 + i / 2] >> 4) & 0x0F);
                } else {
                    stepDirection = (short) (data[4 + i / 2] & 0x0F);
                }
                _nX += stepDirections[stepDirection * 2];
                _nY += stepDirections[stepDirection * 2 + 1];
            }
            final MuPcInstance pc = _client.getActiveChar();
            pc.setDirection((byte) headingDirection);
            pc.moveTo(_nX, _nY);
        } else {
            // disconnect because of hack attempt?
            System.out.println("Incorrect number of steps from "
                    + _client.getActiveChar().getName());
        }

        // if (pc.oldgetKnownObjects() != null) {
        // System.out.println("Known Objects count: " +
        // pc.oldgetKnownObjects().size());
        // ArrayList<MuObject> knownObj = new ArrayList<MuObject>();
        // knownObj.addAll(pc.oldgetKnownObjects().values());
        // ArrayList<MuObject> toDelete = new ArrayList<MuObject>();
        //
        // if (!knownObj.isEmpty()) {
        // for (int i = 0; i < knownObj.size(); i++) {
        // MuObject obj = knownObj.get(i);
        // // std::cout << "O:" << obj->getOId() << "-D>
        // // "<<distance(obj,activeChar)<<"\n";
        // if (!checkInRage(pc, obj)) {
        // System.out.println("to delete"+obj.toString());
        // toDelete.add(obj);
        // }
        // }
        //
        // }
        // if (!toDelete.isEmpty()) {
        // pc.sendPacket(new SForgetId(toDelete));
        // for (int i = 0; i < toDelete.size(); i++) {
        // pc.removeKnownObject(toDelete.get(i));
        // toDelete.get(i).removeKnownObject(pc);
        //
        // }
        // }
        // }
        // Vector visitable =
        // MuWorld.getInstance().getVisibleObjects(pc);
        // System.out.println("Visible Objects count: " + visitable.size());
        // if (visitable.size() != 0) {
        // ArrayList<MuObject> newPc = new ArrayList<MuObject>();
        // ArrayList<MuObject> newNpc = new ArrayList<MuObject>();
        // ArrayList<MuObject> newItem = new ArrayList<MuObject>();
        // //looking for all
        // for (int i = 0; i < visitable.size(); i++) {
        // //when this if isstill unknown for as
        // if (!pc.searchID(((MuObject)visitable.elementAt(i)).getObjectId())) {
        // //If thisis players
        // if (visitable.elementAt(i) instanceof MuPcInstance) {
        // System.out.println("New Player Meeting: "+((MuPcInstance)visitable.elementAt(i)).getName());
        // //Added fim to list
        // newPc.add((MuObject)visitable.elementAt(i));
        // //if thisis monster
        // } else if (visitable.elementAt(i) instanceof MuMonsterInstance) {
        // System.out.println("New NPC Meeting");
        // //added him tolist
        // newNpc.add((MuObject)visitable.elementAt(i));
        // //if item
        // } else if (visitable.elementAt(i) instanceof MuItemOnGround) {
        // System.out.println("New Item on Ground");
        // //added to list
        // newItem.add((MuObject)visitable.elementAt(i));
        // }
        // else {
        // System.out.println("New Unkown Object Meeting!!!");
        // }
        // // Added all to my known lust
        // pc.addKnownObject((MuObject)visitable.elementAt(i));
        // //and also uptade him to know me
        // ((MuObject)visitable.elementAt(i)).addKnownObject(pc);
        // }
        //
        // }
        // if(!newPc.isEmpty()){
        // SPlayersMeeting pcp=new SPlayersMeeting(newPc);
        // pc.sendPacket(pcp);
        // // Notify new visible players of current player
        // ArrayList<MuObject> thisPlayer = new ArrayList<MuObject>();
        // thisPlayer.add(pc);
        // for (int i = 0; i < newPc.size(); i++) {
        // MuPcInstance newPlayer = (MuPcInstance) newPc.get(i);
        // if (!(newPlayer instanceof MuPcActorInstance))
        // newPlayer.sendPacket(new SPlayersMeeting(thisPlayer));
        // }
        // }
        // if (!newNpc.isEmpty()) {
        // SNpcMiting npc = new SNpcMiting(newNpc); // twoze paczke z nowymi Npc
        // pc.sendPacket(npc);
        //
        // }
        // if (!newItem.isEmpty()) {
        // SMeetItemOnGround items = new SMeetItemOnGround(newItem);
        // pc.sendPacket(items);
        // }
        // }

    }

    /**
     * chceck objeci is in range
     * 
     * @param pc
     *            to what
     * @param t
     *            objec
     * @return tru when in range
     */
    public boolean checkInRage(MuPcInstance pc, MuObject t) {
        final int chx = t.getX() / 5;
        final int chy = t.getY() / 5;
        final int myx = pc.getX() / 5;
        final int myy = pc.getY() / 5;
        final int rangeX1 = myx - 3;
        final int rangeX2 = myx + 3;
        final int rangeY1 = myy - 3;
        final int rangeY2 = myy + 3;

        if ((rangeX1 <= chx) && (chx <= rangeX2) && (rangeY1 <= chy)
                && (chy <= rangeY2)) {
            return true;
        }
        return false;

    }

    @Override
    public String getType() {

        return "Charater MOve ";
    }
}
