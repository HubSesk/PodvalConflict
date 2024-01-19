modded class SCR_CampaignMilitaryBaseComponent {
	protected bool m_bIsEnemiesBlockSpawnPoint = false;
	
	override void OnInitialized() {
		super.OnInitialized();
		
		if (!IsProxy() && !m_bIsHQ) {
			GetGame().GetCallqueue().CallLater(HandleEnemiesBlockSpawnPoint, SCR_GameModeCampaign.ENEMIES_BLOCK_SPAWNPOINT_CHECK_INTERVAL, true);
		};
	};
	
	protected void HandleEnemiesBlockSpawnPoint() {
		SCR_GameModeCampaign campaign = SCR_GameModeCampaign.GetInstance();
		if (!campaign)
			return;
		
		if (!m_SpawnPoint)
			return;
		
		if (!campaign.GetIsEnemiesBlockSpawnPoint())
			return;
		
		int radiusSq;
		if (m_eType == SCR_ECampaignBaseType.BASE)
			radiusSq = m_iRadius * m_iRadius;
		else
			radiusSq = RELAY_BASE_RADIUS * RELAY_BASE_RADIUS;
		PlayerManager playerManager = GetGame().GetPlayerManager();
		array<int> playerIds = {};
		playerManager.GetPlayers(playerIds);
		int friendlies = 0;
		int enemies = 0;
		SCR_CampaignFaction baseFaction = GetCampaignFaction();
		vector basePos = GetOwner().GetOrigin();
		
		foreach (int playerId : playerIds)
		{
			SCR_ChimeraCharacter player = SCR_ChimeraCharacter.Cast(playerManager.GetPlayerControlledEntity(playerId));

			if (!player)
				continue;

			CharacterControllerComponent charController = player.GetCharacterController();

			if (charController.IsDead())
				continue;

			if (vector.DistanceSqXZ(player.GetOrigin(), basePos) > radiusSq)
				continue;

			if (player.GetFaction() == baseFaction)
				friendlies++;
			else
				enemies++;
		}
		
		int minEnemiesCountToBlockSpawnPoint = campaign.GetMinEnemiesCountToBlockSpawnPoint();
		float minEnemiesSuperiorityToBlockSpawnPoint = campaign.GetMinEnemiesSuperiorityToBlockSpawnPoint();
		bool isEnemiesBlockSpawnPoint = (enemies >= minEnemiesCountToBlockSpawnPoint) && (enemies >= friendlies * minEnemiesSuperiorityToBlockSpawnPoint);
		if (isEnemiesBlockSpawnPoint != m_bIsEnemiesBlockSpawnPoint) {
			m_bIsEnemiesBlockSpawnPoint = isEnemiesBlockSpawnPoint;
			HandleSpawnPointFaction();
		};
	};
	
	bool IsEnemiesBlockSpawnPoint() {
		return m_bIsEnemiesBlockSpawnPoint;
	};
	
	override protected void HandleSpawnPointFaction() {
		if (!m_SpawnPoint)
			return;
		
		if (IsEnemiesBlockSpawnPoint()) {
			m_SpawnPoint.SetFactionKey(string.Empty);
			return;
		};
		
		super.HandleSpawnPointFaction();
	};
};