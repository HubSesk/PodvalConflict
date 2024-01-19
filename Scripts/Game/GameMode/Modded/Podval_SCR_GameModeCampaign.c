modded class SCR_GameModeCampaign {
	[Attribute("1", desc: "Enable enemies block spawn points at bases.", category: "Campaign", params: "0 inf")]
	protected bool m_bIsEnemiesBlockSpawnPoint;
	
	[Attribute("2", desc: "Minimum enemy players count near to base to block spawn point.", category: "Campaign", params: "0 inf")]
	protected int m_iMinEnemiesCountToBlockSpawnPoint;
	
	[Attribute("2.0", desc: "Minimum enemy players superiority near to base to block spawn point.", category: "Campaign", params: "0.0 inf")]
	protected float m_fMinEnemiesSuperiorityToBlockSpawnPoint;
	
	static const int ENEMIES_BLOCK_SPAWNPOINT_CHECK_INTERVAL = 1000;
	
	bool GetIsEnemiesBlockSpawnPoint() {
		return m_bIsEnemiesBlockSpawnPoint;
	};
	
	int GetMinEnemiesCountToBlockSpawnPoint() {
		return m_iMinEnemiesCountToBlockSpawnPoint;
	};
	
	float GetMinEnemiesSuperiorityToBlockSpawnPoint() {
		return m_fMinEnemiesSuperiorityToBlockSpawnPoint;
	};
};