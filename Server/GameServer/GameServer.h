#pragma once


#include "NtlPacketEncoder_RandKey.h"
#include "NtlFile.h"
#include "Memoryhandle.h"


#include "NtlPacketUG.h"
#include "NtlPacketGU.h"
#include "ResultCode.h"

#include "GsFunctions.h"
#include "QueryClass.h"

#include "NtlItem.h"
#include "Battle.h"
// LOAD TABLES
#include "DragonBallRewardTable.h"
#include "DragonBallTable.h"
#include "Table.h"
#include "NPCTable.h"
#include "TableContainer.h"
#include "WorldTable.h"
#include "MobTable.h"
#include "PCTable.h"
#include "SkillTable.h"
#include "HTBSetTable.h"
#include "TableFileNameList.h"
#include "WorldMapTable.h"
#include "WorldPlayTable.h"
#include "DungeonTable.h"
#include "WorldZoneTable.h"
#include "DirectionLinkTable.h"
#include "ObjectTable.h"
#include "PortalTable.h"
#include "MerchantTable.h"
#include "ItemTable.h"
#include "NewbieTable.h" // For Tutorial
#include "UseItemTable.h" //Added for use items
#include "SystemEffectTable.h" //Added for use some Effects validations and buffs
#include "TimeQuestTable.h"
#include "FormulaTable.h"
#include "ItemMixMachineTable.h"
#include "ExpTable.h"
#include "VehicleTable.h"//Added to use Vehicle -Luiz45
#include "QuestRewardTable.h"
#include "BasicDropTable.h"
#include "EachDropTable.h"
#include "ExcellentDropTable.h"
#include "LegendaryDropTable.h"
#include "NormalDropTable.h"
#include "SuperiorDropTable.h"
#include "MobMovePatternTable.h"
// END TABLES
#include "PlayerInfos.h"
//#include "MainClass.h"
#include "MobActivity.h"
#include "NtlBitFlagManager.h"
#include "PlayerParty.h"
#include <MMSystem.h>
#include <iostream>
#include <map>

enum APP_LOG
{
	PRINT_APP = 2,
};
enum GAME_SESSION
{
	SESSION_CLIENT,
};
struct sSERVERCONFIG
{
	CNtlString		strClientAcceptAddr;
	WORD			wClientAcceptPort;
	CNtlString		Host;
	CNtlString		User;
	CNtlString		Password;
	CNtlString		Database;
	int				PlayerLimit;
	int				PlayerSaveInterval;
	int				PlayerSaveStatsSaveOnlyOnLogout;
};

enum eREWARD_TYPE
{
	eREWARD_TYPE_NORMAL_ITEM,
	eREWARD_TYPE_QUEST_ITEM,
	eREWARD_TYPE_EXP,
	eREWARD_TYPE_SKILL,
	eREWARD_TYPE_ZENY,
	eREWARD_TYPE_CHANGE_CLASS,
	eREWARD_TYPE_BUFF,
	eREWARD_TYPE_PROBABILITY,
	eREWARD_TYPE_REPUTATION,
	eREWARD_TYPE_CHANGE_ADULT,
	eREWARD_TYPE_GET_CONVERT_CLASS_RIGHT,

	eREWARD_TYPE_INVALID				= 0xffffffff
};

const DWORD					MAX_NUMOF_GAME_CLIENT = 5;
const DWORD					MAX_NUMOF_SERVER = 1;
const DWORD					MAX_NUMOF_SESSION = MAX_NUMOF_GAME_CLIENT + MAX_NUMOF_SERVER;

class CGameServer;
class CTableContainer;
class CTableFileNameList;
class CNtlBitFlagManager;

//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
class CClientSession : public CNtlSession
{
public:

	CClientSession(bool bAliveCheck = false, bool bOpcodeCheck = false)
		:CNtlSession( SESSION_CLIENT )
	{
		SetControlFlag( CONTROL_FLAG_USE_SEND_QUEUE );

		if( bAliveCheck )
		{
			SetControlFlag( CONTROL_FLAG_CHECK_ALIVE );
		}

		if( bOpcodeCheck )
		{
			SetControlFlag( CONTROL_FLAG_CHECK_OPCODE );
		}

		SetPacketEncoder( &m_packetEncoder );
	}

	~CClientSession();


public:
	int							OnAccept();
	void						OnClose();
	int							OnDispatch(CNtlPacket * pPacket);

	//
	RwUInt32					GetavatarHandle() { return avatarHandle; }
	RwUInt32					GetTargetSerialId() { return m_uiTargetSerialId; }

	//
	//Client Packet functions
	void						SendGameEnterReq(CNtlPacket * pPacket, CGameServer * app);
	void						SetPlayerAttributeInfo(CGameServer * app, sPC_TBLDAT *pTblData);
	void						SendAvatarCharInfo(CNtlPacket * pPacket, CGameServer * app);
	void						CheckPlayerStat(CGameServer * app, sPC_TBLDAT *pTblData, int level);
	void						SendAvatarItemInfo(CNtlPacket * pPacket, CGameServer * app);
	void						SendAvatarSkillInfo(CNtlPacket * pPacket, CGameServer * app);
	void						SendAvatarHTBInfo(CNtlPacket * pPacket, CGameServer * app);
	void						SendAvatarBuffInfo(CNtlPacket * pPacket, CGameServer * app);
	void						SendAvatarQuestList(CNtlPacket * pPacket, CGameServer * app);
	void						SendSlotInfo(CNtlPacket * pPacket, CGameServer * app);
	void						SendAvatarInfoEnd(CNtlPacket * pPacket);
	void						SendAuthCommunityServer(CNtlPacket * pPacket, CGameServer * app);

	void						SendWorldEnterReq(CNtlPacket * pPacket, CGameServer * app);
//	void						SendPlayerCreate(CNtlPacket * pPacket, CGameServer * app);
	void						SendNpcCreate(CNtlPacket * pPacket, CGameServer * app);
	void						SendMonsterCreate(CNtlPacket * pPacket, CGameServer * app);
	void						SendEnterWorldComplete(CNtlPacket * pPacket);
	//Character Funcs
	void						SendCharReadyReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendTutorialHintReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharReady(CNtlPacket * pPacket);
	void						SendCharMove(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharDestMove(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharMoveSync(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharChangeHeading(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharJump(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharDashKeyBoard(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharDashMouse(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharChangeDirOnFloating(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharFalling(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharExitReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendGameLeaveReq(CNtlPacket * pPacket, CGameServer * app);
	void						RecvServerCommand(CNtlPacket * pPacket, CGameServer * app);
	void						SendUpdateCharSpeed(float fSpeed, CGameServer * app);
	void						SendCharTargetSelect(CNtlPacket * pPacket);
	void						SendCharTargetFacing(CNtlPacket * pPacket);
	void						SendCharTargetInfo(CNtlPacket * pPacket);
	void						SendCharSitDown(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharStandUp(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharSkillUpgrade(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharFollowMove(CNtlPacket * pPacket, CGameServer * app);
	void						SendExcuteTriggerObject(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharBindReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendPortalStartReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendPortalAddReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendPortalTelReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendAttackBegin(CNtlPacket * pPacket, CGameServer * app);
	void						SendAttackEnd(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharToggleFighting(CNtlPacket * pPacket, CGameServer * app);
	void						AddAttackBegin(RwUInt32 uiSerialId, RwUInt32 m_uiTargetSerialId);
	void						RemoveAttackBegin(RwUInt32 uiSerialId, RwUInt32 m_uiTargetSerialId);
	void						SendCharActionAttack(RwUInt32 uiSerialId, RwUInt32 m_uiTargetSerialId, CNtlPacket * pPacket);
	void						SendCharUpdateFaintingState(CNtlPacket * pPacket, CGameServer * app, RwUInt32 uiSerialId, RwUInt32 m_uiTargetSerialId);
	void						SendCharUpdateLp(CNtlPacket * pPacket, CGameServer * app, RwUInt16 wLp, RwUInt32 m_uiTargetSerialId);
	void						SendGmtUpdateReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharRevivalReq(CNtlPacket * pPacket, CGameServer * app);
	//Guild
	void						SendGuildCreateReq(CNtlPacket * pPacket, CGameServer * app);
	//Party
	void						SendPartyInviteReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendCreatePartyReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendDisbandPartyReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendPartyLeaveReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendPartyResponse(CNtlPacket * pPacket, CGameServer * app);
	void						SendPartyChangeDiff(CNtlPacket * pPacket, CGameServer * app);
	void						SendPartyChangeZenny(CNtlPacket * pPacket, CGameServer * app);
	void						SendPartyChangeItem(CNtlPacket * pPacket, CGameServer * app);
	//Mail System
	void						SendCharMailStart(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharMailLoadReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharMailReloadReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharMailReadReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharMailSendReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharMailDelReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharMailItemReceiveReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharMailMultiDelReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharMailLockReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharMailReturnReq(CNtlPacket * pPacket, CGameServer * app);
	//Afk Status
	void						SendCharAwayReq(CNtlPacket * pPacket, CGameServer * app);
	//Shop
	void						SendShopStartReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendShopBuyReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendShopEndReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendShopSellReq(CNtlPacket * pPacket, CGameServer * app);


	void						SendShopSkillReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharLearnSkillReq(CNtlPacket * pPacket, CGameServer * app);
	//ITEMS
	void						SendItemMoveReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendItemDeleteReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendItemStackReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendItemUseReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendItemPickUpReq(CNtlPacket * pPacket, CGameServer * app); //Item pickup

	//MISC
	void						SendRollDice(CNtlPacket * pPacket, CGameServer * app);
	void						SendFogOfWarRes(CNtlPacket * pPacket, CGameServer * app);
	void						SendRideOnBusRes(CNtlPacket * pPacket, CGameServer * app);
	void						SendRideOffBusRes(CNtlPacket * pPacket, CGameServer * app);
	void						SendBusLocation(CNtlPacket * pPacket, CGameServer * app);
	void						SendNetPyStart(CNtlPacket * pPacket, CGameServer * app);
	// SCOUTER
	void						SendScouterIndicatorReq(CNtlPacket * pPacket, CGameServer * app);
	// DRAGON BALL
	void						SendDragonBallCheckReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendDragonBallRewardReq(CNtlPacket * pPacket, CGameServer * app);
	// SKILL
	void						SendCharSkillAction(CNtlPacket * pPacket, CGameServer * app, sSKILL_TBLDAT* skill, int RpSelectedType);
	void						SendCharSkillRes(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharSkillCasting(CNtlPacket * pPacket, CGameServer * app, sSKILL_TBLDAT* skill, int RpSelectedType);
	void						SendCharSkillTransformCancel(CNtlPacket * pPacket, CGameServer * app);
	void						SendSocialSkillRes(CNtlPacket *pPacket, CGameServer * app);
	void						SendRpCharge(CNtlPacket *pPacket, CGameServer * app);
	void						SendCharSkillBuffDrop(CNtlPacket *pPacket, CGameServer * app);

	//HTB
	void						SendCharSkillHTBLearn(CNtlPacket * pPacket, CGameServer * app);
	void						SendHTBStartReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendHTBFoward(CNtlPacket * pPacket, CGameServer * app);
	void						SendHTBRpBall(CNtlPacket * pPacket, CGameServer * app);
	void						SendCharUpdateHTBState(int SkillID, CGameServer * app);
	void						SendHTBSendbagState(CGameServer * app);

	// QuickSlots
	void						SendCharUpdQuickSlot(CNtlPacket * pPacket, CGameServer * app);
 	void						SendCharDelQuickSlot(CNtlPacket * pPacket, CGameServer * app);
	
	// MUDOSA
	void						SendGambleBuyReq(CNtlPacket * pPacket, CGameServer * app);
	// BANK
	void						SendBankStartReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendBankEndReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendBankBuyReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendBankLoadReq(CNtlPacket * pPacket, CGameServer * app);
	// LOOT
	void						SendMobLoot(CNtlPacket * pPacket, CGameServer * app, RwUInt32 m_uiTargetSerialId);
	void						SendZennyPickUpReq(CNtlPacket * pPacket, CGameServer * app);
	// LEVEL UP
	void						SendPlayerLevelUpCheck(CGameServer * app, int exp);
	// Wafog
	void						SendAvatarWarFogInfo(CNtlPacket * pPacket, CGameServer * app);
	// QUEST
	void						SendPlayerQuestReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendObjectVisitQuest(CNtlPacket * pPacket, CGameServer * app);
	void						SendTSUpdateState(CNtlPacket * pPacket, CGameServer * app);
	//HoiPoi
	void						SendHoiPoiJob(CNtlPacket * pPacket, CGameServer * app);
	void						SendHoiPoiJobReset(CNtlPacket * pPacket, CGameServer * app);
	//Tutorial
	void						SendTutorialPlayQuit(CNtlPacket * pPacket, CGameServer * app);
	void						SendDirectPlay(CNtlPacket * pPacket, CGameServer * app);
	//Party Dungeon
	void						SendInitPartyDungeon(CNtlPacket * pPacket, CGameServer * app);
	//TIMEQUEST
	void						SendTimeQuestList(CNtlPacket * pPacket, CGameServer * app);
	void						LeaveTimeQuestRoom(CNtlPacket * pPacket, CGameServer * app);
	void						JoinTimeQuestRoom(CNtlPacket * pPacket, CGameServer * app);
	void						SendTimeQuestTeleport(CNtlPacket * pPacket, CGameServer * app);
	//Private Shop
	void						SendPrivateShopCreate(CNtlPacket * pPacket, CGameServer * app);
	void						SendPrivateShopExit(CNtlPacket * pPacket, CGameServer * app);
	// DUEL
	void						SendFreeBattleReq(CNtlPacket * pPacket, CGameServer * app);
	void						SendFreeBattleAccpetReq(CNtlPacket * pPacket, CGameServer * app);
	//Game Server functions
	sGU_OBJECT_CREATE			characterspawnInfo;
	//
	PlayerInfos					*plr;
	GsFunctionsClass			*gsf;
private:
	CNtlPacketEncoder_RandKey	m_packetEncoder;
	RwUInt32					avatarHandle;


public:
	int		IsMonsterIDInsideList(TBLIDX MonsterSpawnID)
	{
		MyMonsterList * mymonsterlist;
		if (my_monsterList.empty() == false) {
			for( MYMONSTERLISTIT it = my_monsterList.begin(); it != my_monsterList.end(); it++ )
			{
				mymonsterlist = (*it);
				if(mymonsterlist->MonsterID == MonsterSpawnID)
				{
					return mymonsterlist->MobTBLIDX;
				}
			}
		}
		return 0;
	}
	bool		IsMonsterInsideList(TBLIDX MonsterSpawnID)
	{
		MyMonsterList * mymonsterlist;
		if (my_monsterList.empty() == false) {
			for( MYMONSTERLISTIT it = my_monsterList.begin(); it != my_monsterList.end(); it++ )
			{
				mymonsterlist = (*it);
				if(mymonsterlist->MonsterID == MonsterSpawnID)
				{
					return true;
				}
			}
		}
		return false;
	}
	void		InsertIntoMyMonsterList(TBLIDX MonsterSpawnID, CNtlVector Position, TBLIDX mobid)
	{
		MyMonsterList * myml = new MyMonsterList;

		myml->MonsterID = MonsterSpawnID;
		myml->Position = Position;
		myml->MobTBLIDX = mobid;

		my_monsterList.push_back(myml);
	}
	bool		RemoveFromMyMonsterList(TBLIDX MonsterSpawnID)
	{
		MyMonsterList * mymonsterlist;
		for( MYMONSTERLISTIT it = my_monsterList.begin(); it != my_monsterList.end(); it++ )
		{
			mymonsterlist = (*it);
			if(mymonsterlist->MonsterID == MonsterSpawnID)
			{
				it = my_monsterList.erase(it);
				return true;
			}
		}
		return true;
	}
typedef struct _MyMonsterList
{
	TBLIDX			MonsterID;
	CNtlVector		Position;
	TBLIDX			MobTBLIDX;

}MyMonsterList;
typedef std::list<MyMonsterList*> MYMONSTERLIST;
typedef MYMONSTERLIST::iterator MYMONSTERLISTIT;
MYMONSTERLIST					my_monsterList;
	void		InsertIntoMyNpcList(TBLIDX NpcSpawnID, CNtlVector Position)
	{
		MyNpcList * mynl = new MyNpcList;

		mynl->NpcID = NpcSpawnID;
		mynl->Position = Position;

		my_npcList.push_back(mynl);
	}
	bool		IsNpcInsideList(TBLIDX NpcSpawnID)
	{
		MyNpcList * mynpclist;
		for( MYNPCLISTIT it = my_npcList.begin(); it != my_npcList.end(); it++ )
		{
			mynpclist = (*it);
			if(mynpclist->NpcID == NpcSpawnID)
			{
				return true;
			}
		}
		return false;
	}
	typedef struct _MyNpcList
	{
		TBLIDX			NpcID;
		CNtlVector		Position;

	}MyNpcList;
	typedef std::list<MyNpcList*> MYNPCLIST;
	typedef MYNPCLIST::iterator MYNPCLISTIT;
	MYNPCLIST					my_npcList;
	void		FillNewList(MYMONSTERLIST *mylist)
	{
		for( MYMONSTERLISTIT it = my_monsterList.begin(); it != my_monsterList.end(); it++ )
		{
			mylist->push_back(*it);
		}
	}
};
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//

class CGameSessionFactory : public CNtlSessionFactory
{
public:

	CNtlSession * CreateSession(SESSIONTYPE sessionType)
	{
		CNtlSession * pSession = NULL;
		switch( sessionType )
		{
		case SESSION_CLIENT: 
			{
				pSession = new CClientSession;
			}
			break;

		default:
			break;
		}

		return pSession;
	}
};

//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//

class CGameServer : public CNtlServerApp
{

public:
	int					OnInitApp()
	{
		m_nMaxSessionCount = MAX_NUMOF_SESSION;
		m_pSessionFactory = new CGameSessionFactory;
		if( NULL == m_pSessionFactory )
		{
			return NTL_ERR_SYS_MEMORY_ALLOC_FAIL;
		}
		return NTL_SUCCESS;
	}
	const char*		GetConfigFileHost()
	{
		return m_config.Host.c_str();
	}
	const char*		GetConfigFileUser()
	{
		return m_config.User.c_str();
	}
	const char*		GetConfigFilePassword()
	{
		return m_config.Password.c_str();
	}
	const char*		GetConfigFileDatabase()
	{
		return m_config.Database.c_str();
	}
	int					OnCreate()
	{
		int rc = NTL_SUCCESS;
		rc = m_clientAcceptor.Create(	m_config.strClientAcceptAddr.c_str(), m_config.wClientAcceptPort, SESSION_CLIENT,MAX_NUMOF_GAME_CLIENT, 5, 2, MAX_NUMOF_GAME_CLIENT );
		if ( NTL_SUCCESS != rc )
		{
			return rc;
		}
		rc = m_network.Associate( &m_clientAcceptor, true );
		if( NTL_SUCCESS != rc )
		{
			return rc;
		}
		return NTL_SUCCESS;
	}
	void				OnDestroy()
	{
	}
	int					OnCommandArgument(int argc, _TCHAR* argv[])
	{
		return NTL_SUCCESS;
	}
	int					OnConfiguration(const char * lpszConfigFile)
	{
		CNtlIniFile file;
		int rc = file.Create( lpszConfigFile );
		if( NTL_SUCCESS != rc )
		{
			return rc;
		}
		if( !file.Read("Game Server", "Address", m_config.strClientAcceptAddr) )
		{
			return NTL_ERR_SYS_CONFIG_FILE_READ_FAIL;
		}
		if( !file.Read("Game Server", "Port",  m_config.wClientAcceptPort) )
		{
			return NTL_ERR_SYS_CONFIG_FILE_READ_FAIL;
		}
		if( !file.Read("DATABASE", "Host",  m_config.Host) )
		{
			return NTL_ERR_DBC_HANDLE_ALREADY_ALLOCATED;
		}
		if( !file.Read("DATABASE", "User",  m_config.User) )
		{
			return NTL_ERR_SYS_MEMORY_ALLOC_FAIL;
		}
		if( !file.Read("DATABASE", "Password",  m_config.Password) )
		{
			return NTL_ERR_SYS_LOG_SYSTEM_INITIALIZE_FAIL;
		}
		if( !file.Read("DATABASE", "Db",  m_config.Database) )
		{
			return NTL_ERR_DBC_CONNECTION_CONNECT_FAIL;
		}
		/*if( !file.Read("PERFORMANCE", "PlayerLimit",  m_config.PlayerLimit) )
		{
			return NTL_ERR_SYS_CONFIG_FILE_READ_FAIL;
		}
		if( !file.Read("PERFORMANCE", "PlayerSaveInterval",  m_config.PlayerSaveInterval) )
		{
			return NTL_ERR_SYS_CONFIG_FILE_READ_FAIL;
		}
		if( !file.Read("PERFORMANCE", "PlayerSaveStatsSaveOnlyOnLogout",  m_config.PlayerSaveStatsSaveOnlyOnLogout) )
		{
			return NTL_ERR_SYS_CONFIG_FILE_READ_FAIL;
		}*/
		return NTL_SUCCESS;
	}
	int					OnAppStart()
	{
		dwThreadId = 0;
		if(CreateTableContainer(1))
		{
			return NTL_SUCCESS;
		}else{
		printf("FAILED LOADING TABLES !!! \n");
		return NTL_SUCCESS;
		}
	}

private:
	CNtlAcceptor				m_clientAcceptor;
	CNtlLog  					m_log;
	sSERVERCONFIG				m_config;
public:
	MySQLConnWrapper			*db;
	MobActivity					*mob;
	QueryClass					*qry;
public:
	void						UpdateClient(CNtlPacket * pPacket, CClientSession *	pSession);
	CNtlPacket *				pPacket;
	CClientSession *			pSession;
	CTableContainer	*			g_pTableContainer;
	bool						CreateTableContainer(int byLoadMethod);

	void						Run()
	{
		DWORD dwTickCur, dwTickOld = ::GetTickCount();

		while( IsRunnable() )
		{		
			dwTickCur = ::GetTickCount();
			if( dwTickCur - dwTickOld >= 1000 )
			{
				UpdateClient(pPacket,pSession);
				dwTickOld = dwTickCur;
			}
		Sleep(100);
		}
	}

	bool						AddUser(const char * lpszUserID, CClientSession * pSession)
	{
		if( false == m_userList.insert( USERVAL(CNtlString(lpszUserID), pSession)).second )
		{
			return false;
		}
		return true;		
	}
	void						RemoveUser(const char * lpszUserID)
	{
		m_userList.erase( CNtlString(lpszUserID) );
	}
	bool						FindUser(const char * lpszUserID)
	{
		USERIT it = m_userList.find( CNtlString(lpszUserID) );
		if( it == m_userList.end() )
			return false;
		return true;
	}
	void						UserBroadcast(CNtlPacket * pPacket)
	{
		for( USERIT it = m_userList.begin(); it != m_userList.end(); it++ )
		{
			it->second->PushPacket( pPacket );
		}
	}
	void						GetUserSession(int handle, PlayerInfos *requested)
	{
		for( USERIT it = m_userList.begin(); it != m_userList.end(); it++ )
		{
			if(it->second->plr->GetAvatarandle() == handle)
			{
				memcpy(requested, it->second->plr, sizeof (PlayerInfos));
				break;
			}
		}
	}
	void						UserBroadcastothers(CNtlPacket * pPacket, CClientSession * pSession)
	{
		for( USERIT it = m_userList.begin(); it != m_userList.end(); it++ )
		{
			if(pSession->GetavatarHandle() != it->second->GetavatarHandle())
			it->second->PushPacket( pPacket );
		}
	}
	void						UserBroadcasFromOthers(eOPCODE_GU opcode, CClientSession * pSession)
	{
		if(opcode == GU_OBJECT_CREATE)
		{
			for( USERIT it = m_userList.begin(); it != m_userList.end(); it++ )
			{
				if(pSession->GetavatarHandle() != it->second->GetavatarHandle())
				{
					CNtlPacket packet(sizeof(sGU_OBJECT_CREATE));
					sGU_OBJECT_CREATE * sPacket = (sGU_OBJECT_CREATE *)packet.GetPacketData();
					memcpy(sPacket, &it->second->characterspawnInfo, sizeof(sGU_OBJECT_CREATE));
					sPacket->handle = it->second->GetavatarHandle();

					packet.SetPacketLen( sizeof(sGU_OBJECT_CREATE) );
					pSession->PushPacket(&packet);
				}
			}
		}
	}

	void		InsertMonsterIntoAllMyMonsterLists(CNtlPacket * pPacket, TBLIDX MonsterSpawnID, CNtlVector Position, TBLIDX MonsterID)
	{
		for( USERIT it = m_userList.begin(); it != m_userList.end(); it++ )
		{
			it->second->InsertIntoMyMonsterList(MonsterSpawnID, Position, MonsterID);
		}
	}
	void		RemoveMonsterFromAllMyMonsterLists(TBLIDX MonsterSpawnID)
	{
		for( USERIT it = m_userList.begin(); it != m_userList.end(); it++ )
		{
			it->second->RemoveFromMyMonsterList(MonsterSpawnID);
		}
	}
	bool			AddNewZennyAmount(int handle, int amount)
	{
		if( false == amount_zenny.insert( ZENNYAMOUNTVAL(handle, amount)).second )
		{
			return false;
		}
		return true;		
	}
	void			RemoveZenny(const int handle)
	{
		amount_zenny.erase(handle);
	}
	int				FindZenny(const int handle)
	{
		int amount_ = 0;
		ZENNYAMOUNTIT it = amount_zenny.find(handle);
		if( it == amount_zenny.end() )
			return -1;
		else
			return amount_zenny[handle];
	}
	DWORD			ThreadRequest()
	{
		dwThreadId += 1;
		return dwThreadId;
	};
	DWORD		dwThreadId;
	typedef std::map<CNtlString, CClientSession*> USERLIST;
	typedef USERLIST::value_type USERVAL;
	typedef USERLIST::iterator USERIT;
	USERLIST					m_userList;

	typedef std::map<int, int> ZENNYAMOUNT;
	typedef ZENNYAMOUNT::value_type ZENNYAMOUNTVAL;
	typedef ZENNYAMOUNT::iterator ZENNYAMOUNTIT;
	ZENNYAMOUNT					amount_zenny;
};

