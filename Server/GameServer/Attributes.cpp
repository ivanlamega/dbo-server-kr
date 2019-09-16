#include "stdafx.h"
#include "Attributes.h"
#include "GameServer.h"

PlayerAttributes::PlayerAttributes(HSESSION PlayerSession)
{
	this->PlayerSession = PlayerSession;
}

PlayerAttributes::~PlayerAttributes()
{
}
/**
*  Load Attributes From DB this will set all sPlayerAttribute with Database Values
*  To Return this values you need use getAvatarAttribute();
*/
void PlayerAttributes::LoadAttributesFromDB(int charID)
{
	CGameServer * app = (CGameServer*)NtlSfxGetApp();
	MySQLConnWrapper *db = new MySQLConnWrapper;
	db->setConfig(app->GetConfigFileHost(), app->GetConfigFileUser(), app->GetConfigFilePassword(), app->GetConfigFileDatabase());
	db->connect();
	db->switchDb(app->GetConfigFileDatabase());

	db->prepare("SELECT * FROM characters WHERE CharID = ?");
	db->setInt(1, charID);
	db->execute();
	db->fetch();
	int level = db->getInt("Level");
	sPC_TBLDAT *pTblData;
	//Load All Attributes One time only - Luiz  IN ORDER --Kalisto
	//STR 
	this->sPlayerAttribute.byBaseStr = pTblData->byStr;// db->getInt("BaseStr") + db->getInt("Level")*0.2;
	this->sPlayerAttribute.byLastStr = db->getInt("LastStr");
	//Constitucion
	this->sPlayerAttribute.byBaseCon = pTblData->byCon;// db->getInt("BaseCon") * db->getInt("Level")*0.2;
	this->sPlayerAttribute.byLastCon = db->getInt("LastCon");
	//Focus
	this->sPlayerAttribute.byBaseFoc = pTblData->byFoc;// db->getInt("BaseFoc") * db->getInt("Level")*0.2;
	this->sPlayerAttribute.byLastFoc = db->getInt("LastFoc");
	//Dextry
	this->sPlayerAttribute.byBaseDex = pTblData->byDex;// db->getInt("BaseDex") * db->getInt("Level")*0.2;
	this->sPlayerAttribute.byLastDex = db->getInt("LastDex");
	//Soul
	this->sPlayerAttribute.byBaseSol = pTblData->bySol;// *db->getInt("Level")*0.2;
	this->sPlayerAttribute.byLastSol = db->getInt("LastSol");
	//Energy
	this->sPlayerAttribute.byBaseEng = pTblData->byEng;// db->getInt("BaseEng") * db->getInt("Level")*0.2;
	this->sPlayerAttribute.byLastEng = db->getInt("BaseEng");
	//EP/LP
	this->sPlayerAttribute.wBaseMaxLP = pTblData->wBasic_LP;
	this->sPlayerAttribute.wLastMaxLP = (pTblData->byCon * 10) + (db->getInt("LastMaxLP") * 0.2);
	this->sPlayerAttribute.wBaseMaxEP = pTblData->wBasic_EP;
	this->sPlayerAttribute.wLastMaxEP = (pTblData->bySol * 10) + (db->getInt("LastMaxEP") * 0.2);
	//Physical Atack
	this->sPlayerAttribute.wBasePhysicalOffence = pTblData->wBasic_Energy_Offence;// db->getInt("BasePhysicalOffence") * db->getInt("Level")*1.5;
	this->sPlayerAttribute.wLastPhysicalOffence = (pTblData->byStr * 5) + (db->getInt("LastPhysicalOffence") * db->getInt("Level") * 1.5);
	//Physical Defese
	this->sPlayerAttribute.wBasePhysicalDefence = pTblData->wBasic_Physical_Defence;// db->getInt("BasePhysicalDefence") * db->getInt("Level")*1.2;
	this->sPlayerAttribute.wLastPhysicalDefence = (pTblData->byDex * 5) + (db->getInt("LastPhysicalDefence") * db->getInt("Level") * 1.5);
	//Energy Atack
	this->sPlayerAttribute.wBaseEnergyOffence = pTblData->wBasic_Energy_Offence;// db->getInt("BaseEnergyOffence") * db->getInt("Level")*0.2;
	this->sPlayerAttribute.wLastEnergyOffence = (pTblData->bySol * 5) + (db->getInt("LastEnergyOffence") * db->getInt("Level") * 0.2);
	//Energy Defese
	this->sPlayerAttribute.wBaseEnergyDefence = pTblData->wBasic_Energy_Defence;// db->getInt("BaseEnergyDefence") * db->getInt("Level")*0.2;
	this->sPlayerAttribute.wLastEnergyDefence = (pTblData->byEng * 5) + (db->getInt("LastEnergyDefence") * db->getInt("Level") * 0.2);
	//Hit Rate
	this->sPlayerAttribute.wBaseAttackRate = pTblData->wAttack_Rate;// db->getInt("BaseAttackRate") * db->getInt("Level")*0.2;
	this->sPlayerAttribute.wLastAttackRate = (pTblData->byFoc * 5) + (db->getInt("LastEnergyDefence") * db->getInt("Level") * 0.2);
	//Dogge Rate
	this->sPlayerAttribute.wBaseDodgeRate = pTblData->wDodge_Rate;// db->getInt("BaseDodgeRate") * db->getInt("Level")*0.2;
	this->sPlayerAttribute.wLastDodgeRate = (pTblData->byDex * 5) + (db->getInt("LastDodgeRate") * db->getInt("Level") * 0.2);
	//Physical Critical Rate
	this->sPlayerAttribute.wBasePhysicalCriticalRate = pTblData->byDex;// db->getInt("BasePhysicalCriticalRate") * db->getInt("Level")*0.2;
	this->sPlayerAttribute.wLastPhysicalCriticalRate = (pTblData->byDex) * (db->getInt("Level") * 0.2);
	//Energy Critical Rate
	this->sPlayerAttribute.wBaseEnergyCriticalRate = pTblData->byFoc;// db->getInt("BaseEnergyCriticalRate") * db->getInt("Level")*0.2;
	this->sPlayerAttribute.wLastEnergyCriticalRate = (pTblData->byFoc) * (db->getInt("Level") * 0.2);
	//RP 
	this->sPlayerAttribute.wBaseMaxRP = 0;// db->getInt("BaseMaxRP");
	this->sPlayerAttribute.wLastMaxRP = 0;// db->getInt("LastMaxRP");
	//Block Rate 
	this->sPlayerAttribute.wBaseBlockRate = pTblData->wBlock_Rate;//db->getInt("BaseBlockRate");
	this->sPlayerAttribute.wLastBlockRate = db->getInt("LastBlockRate");// db->getInt("LastBlockRate");
	//Run Speed
	//this->sPlayerAttribute.fLastRunSpeed = (float)pTblData->;// (float)db->getDouble("LastRunSpeed");
	//Atack Speed
	this->sPlayerAttribute.wBaseAttackSpeedRate = 0;// (float)db->getInt("BaseAttackSpeedRate");
	this->sPlayerAttribute.wLastAttackSpeedRate = 0;//(float)db->getInt("LastAttackSpeedRate");
	//Atack Range
	this->sPlayerAttribute.fBaseAttackRange = pTblData->fAttack_Range / 2;// (float)db->getInt("BaseAttackRange");
	this->sPlayerAttribute.fLastAttackRange = pTblData->fAttack_Range / 2;// (float)db->getInt("LastAttackRange");
	//nao sei....
	/*this->sPlayerAttribute.unknown_int16[0] = 0;
	this->sPlayerAttribute.unknown_int16[1] = 0;
	this->sPlayerAttribute.unknown_int16[2] = 0;
	this->sPlayerAttribute.unknown_int16[3] = 0;*/
	//LP Get up Reg
	this->sPlayerAttribute.wBaseLpRegen = 20;
	this->sPlayerAttribute.wLastLpRegen = 20;
	//LP Sit Down Reg
	this->sPlayerAttribute.wBaseLpSitdownRegen = 6;
	this->sPlayerAttribute.wLastLpSitdownRegen = 7;
	//LP Reg in Batle
	this->sPlayerAttribute.wBaseLpBattleRegen = 8;
	this->sPlayerAttribute.wLastLpBattleRegen = 9;
	//EP Get UP Reg
	this->sPlayerAttribute.wBaseEpRegen = 20;
	this->sPlayerAttribute.wLastEpRegen = 20;
	//EP Sit Down Reg
	this->sPlayerAttribute.wBaseEpSitdownRegen = 12;
	this->sPlayerAttribute.wLastEpSitdownRegen = 13;
	//EP Reg in Batle
	this->sPlayerAttribute.wBaseEpBattleRegen = 14;
	this->sPlayerAttribute.wLastEpBattleRegen = 15;
	//Rp incress rate
	this->sPlayerAttribute.wBaseRpRegen = 0;
	this->sPlayerAttribute.wLastRpRegen = 0;
	//RP diminution
	this->sPlayerAttribute.wLastRpDimimutionRate = 0;
	//Curse Sucess Rate
	this->sPlayerAttribute.wBaseCurseSuccessRate = pTblData->wCurse_Success_Rate;
	this->sPlayerAttribute.wLastCurseSuccessRate = (pTblData->byFoc * 5) + (db->getInt("LastCurseSuccessRate") * 0.2);
	//Curse Tolerance Rate
	this->sPlayerAttribute.wBaseCurseToleranceRate = pTblData->wCurse_Tolerance_Rate;
	this->sPlayerAttribute.wLastCurseToleranceRate = (pTblData->byCon * 5) + (db->getInt("LastCurseToleranceRate") * 0.2);
	//Nao sei
	this->sPlayerAttribute.fCastingTimeChangePercent = 0;
	this->sPlayerAttribute.fCoolTimeChangePercent = 0;
	this->sPlayerAttribute.fKeepTimeChangePercent = 0;
	this->sPlayerAttribute.fDotValueChangePercent = 0;
	this->sPlayerAttribute.fDotTimeChangeAbsolute = 0;
	this->sPlayerAttribute.fRequiredEpChangePercent = 0;
	//Atribute Ofense/Defese
	this->sPlayerAttribute.fHonestOffence = 0;//nao
	this->sPlayerAttribute.fHonestDefence = 0;//nao
	this->sPlayerAttribute.fStrangeOffence = 0;//nao
	this->sPlayerAttribute.fStrangeDefence = 0;//nao
	this->sPlayerAttribute.fWildOffence = 0;//nao
	this->sPlayerAttribute.fWildDefence = 0;//nao
	this->sPlayerAttribute.fEleganceOffence = 0;//nao
	this->sPlayerAttribute.fEleganceDefence = 0;//nao
	this->sPlayerAttribute.fFunnyOffence = 0;//nao
	this->sPlayerAttribute.fFunnyDefence = 0;//nao

	this->sPlayerAttribute.wParalyzeToleranceRate = 0;//nao
	this->sPlayerAttribute.wTerrorToleranceRate = 0;//nao
	this->sPlayerAttribute.wConfuseToleranceRate = 0;//nao
	this->sPlayerAttribute.wStoneToleranceRate = 0;//nao
	this->sPlayerAttribute.wCandyToleranceRate = 0;//nao
	this->sPlayerAttribute.fParalyzeKeepTimeDown = 0;//nao
	this->sPlayerAttribute.fTerrorKeepTimeDown = 0;//nao
	this->sPlayerAttribute.fConfuseKeepTimeDown = 0;//nao
	this->sPlayerAttribute.fStoneKeepTimeDown = 0;//nao
	this->sPlayerAttribute.fCandyKeepTimeDown = 0;//nao
	this->sPlayerAttribute.fBleedingKeepTimeDown = 0;//nao
	this->sPlayerAttribute.fPoisonKeepTimeDown = 0;
	this->sPlayerAttribute.fStomachacheKeepTimeDown = 0;
	this->sPlayerAttribute.fCriticalBlockSuccessRate = 0;
	this->sPlayerAttribute.wGuardRate = 0;
	this->sPlayerAttribute.fSkillDamageBlockModeSuccessRate = 0;
	this->sPlayerAttribute.fCurseBlockModeSuccessRate = 0;
	this->sPlayerAttribute.fKnockdownBlockModeSuccessRate = 0;

	this->sPlayerAttribute.fHtbBlockModeSuccessRate = 0; // Bleeding defense TW
	this->sPlayerAttribute.fSitDownLpRegenBonusRate = 0; // posion defense tw
	this->sPlayerAttribute.fSitDownEpRegenBonusRate = 0; // abdominal pain defense
	this->sPlayerAttribute.fPhysicalCriticalDamageBonusRate = 0;//Burn Defense

	this->sPlayerAttribute.fEnergyCriticalDamageBonusRate = 1;
	this->sPlayerAttribute.fItemUpgradeBonusRate = 2;
	this->sPlayerAttribute.fItemUpgradeBreakBonusRate = 3;
/*	this->sPlayerAttribute.fBaseAirDash2Speed = 30.0f;//Dash Fly2 TW
	this->sPlayerAttribute.fLastAirDash2Speed = 30.0f;//Dash Fly2 TW
	this->sPlayerAttribute.fBaseAirDashSpeed = 20.0f;//Dash Fly TW
	this->sPlayerAttribute.fLastAirDashSpeed = 20.0f;//Dash Fly TW
	this->sPlayerAttribute.fBaseRunSpeed = (float)pcDat->child_run_speed_origin;//Base Run TW
	this->sPlayerAttribute.fLastAirSpeed = 15;//LastAir Speed TW
	this->sPlayerAttribute.wLastMaxAp = 450000;// db->getInt("LastMaxAp");//Max AP
	this->sPlayerAttribute.wBaseMaxAp = 450000;// db->getInt("BaseMaxAp");//Base Max Ap
	this->sPlayerAttribute.wBaseApBattleRegen = 5000;//Regen In Battle AP TW
	this->sPlayerAttribute.wLastApBattleRegen = 5000;//LAst Regen in Battle Ap TW
	this->sPlayerAttribute.wBaseApRegen = 5000;//Base Ap Regen TW
	this->sPlayerAttribute.wLastApRegen = 5000;//Base While Sitting Regen AP TW
	this->sPlayerAttribute.wBaseApSitdownRegen = 5000;//AP Regen TW
	this->sPlayerAttribute.wLastApSitdownRegen = 5000;//AP Regen TW*/


}
//This method will return a sAVATAR_ATTRIBUTE struct
sAVATAR_ATTRIBUTE PlayerAttributes::GetAvatarAttribute()
{
	return this->sPlayerAttribute;
}
//This method will return a sAVATAR_ATTRIBUTE_LINK
//Initially the sPlayerAttributeLink is not filled, you need call UpdateAvatarAttribute(RwUint32 Handle) to Fill
sAVATAR_ATTRIBUTE_LINK PlayerAttributes::GetAvatarAttributeLink()
{
	return this->sPlayerAttributeLink;
}
/**
* As said you need send your handle and this will update all attributes and will send a Packet(GU_AVATAR_ATTRIBUTE)
*/
void PlayerAttributes::UpdateAvatarAttributes(RwUInt32 Handle)
{
	CNtlPacket packet(sizeof(sGU_AVATAR_ATTRIBUTE_UPDATE));
	sGU_AVATAR_ATTRIBUTE_UPDATE * res = (sGU_AVATAR_ATTRIBUTE_UPDATE *)packet.GetPacketData();
	PlayerInfos* plr;
	memcpy(&this->sPlayerAttribute, &plr->pcProfile->avatarAttribute, sizeof(sAVATAR_ATTRIBUTE));

	CNtlBitFlagManager changedFlag;

	changedFlag.Create(&this->sPlayerAttribute, ATTRIBUTE_TO_UPDATE_COUNT);
	this->sPlayerAttributeLink = CNtlAvatar::GetInstance()->ConvertAttributeToAttributeLink(&this->sPlayerAttribute);

	DWORD buffer[2048];//Thanks Daneos
	DWORD datasize;

	for (BYTE byIndex = ATTRIBUTE_TO_UPDATE_FIRST; byIndex <= ATTRIBUTE_TO_UPDATE_LAST; byIndex++)
	{
		changedFlag.Set(byIndex);
	}

	if (CNtlAvatar::GetInstance()->SaveAvatarAttribute(&changedFlag, &this->sPlayerAttributeLink, &buffer, &datasize) == false)
	{
		printf("ERROR IN UPDATE ATTRIBUTE");
	}

	memcpy(res->abyFlexibleField, &buffer, ((UCHAR_MAX - 1) / 8 + 1) + sizeof(sAVATAR_ATTRIBUTE));

	res->byAttributeTotalCount = ATTRIBUTE_TO_UPDATE_LAST;
	res->hHandle = Handle;
	res->wOpCode = GU_AVATAR_ATTRIBUTE_UPDATE;

	packet.SetPacketLen(sizeof(sGU_AVATAR_ATTRIBUTE_UPDATE));
	g_pApp->Send(this->PlayerSession, &packet);
	plr = NULL;
	delete plr;
}
/*
* This function will update the Attributes by Chip Info - Need be Implemented - Luiz45
*/
void PlayerAttributes::UpdateStatsUsingScouterChips(RwUInt32 Handle, TBLIDX OptionTblidx, bool bDecrease)
{
	CGameServer * app = (CGameServer*)NtlSfxGetApp();
	CItemOptionTable* pItemOptionTable = app->g_pTableContainer->GetItemOptionTable();
	sITEM_OPTION_TBLDAT* sItemOptTbl = reinterpret_cast<sITEM_OPTION_TBLDAT*>(pItemOptionTable->FindData(OptionTblidx));
	PlayerInfos* plr;
	//Let's Check what we gonna update
	switch (sItemOptTbl->byScouterInfo)
	{
	case SCOUTER_INFO_LP:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.wBaseMaxLP -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.wBaseMaxLP += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_EP:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.wBaseMaxEP -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.wBaseMaxEP += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_ATTACK_RATE:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.wLastAttackRate -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.wLastAttackRate += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_ATTACK_SPEED:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.wLastAttackSpeedRate -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.wLastAttackSpeedRate += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_BLOCK_RATE:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.wLastBlockRate -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.wLastBlockRate += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_CON:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.byLastCon -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.byLastCon += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_CURSE_SUCCESS_RATE:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.wLastCurseSuccessRate -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.wLastCurseSuccessRate += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_CURSE_TOLERANCE_RATE:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.wLastCurseToleranceRate -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.wLastCurseToleranceRate += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_DEX:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.byLastDex -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.byLastDex += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_DODGE_RATE:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.wLastDodgeRate -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.wLastDodgeRate += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_ENG:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.byLastEng -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.byLastEng += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_FOC:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.byLastFoc -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.byLastFoc += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_ITEM_BREAK_RATE_DOWN:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.fItemUpgradeBreakBonusRate -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.fItemUpgradeBreakBonusRate += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_SOL:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.byLastSol -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.byLastSol += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_STR:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.byLastStr -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.byLastStr += sItemOptTbl->nValue[0];
	}
	break;
	case SCOUTER_INFO_UPGRADE_RATE_UP:
	{
		if (bDecrease)
			plr->pcProfile->avatarAttribute.fItemUpgradeBonusRate -= sItemOptTbl->nValue[0];
		else
			plr->pcProfile->avatarAttribute.fItemUpgradeBonusRate += sItemOptTbl->nValue[0];
	}
	break;
	default:
	{
		//Not Implemented yet
		printf("Case not implemented yet, case struct number: %i", sItemOptTbl->byScouterInfo);
	}
	break;
	}
	memcpy(&this->sPlayerAttribute, &plr->pcProfile->avatarAttribute, sizeof(sAVATAR_ATTRIBUTE));
	this->UpdateAvatarAttributes(Handle);
}