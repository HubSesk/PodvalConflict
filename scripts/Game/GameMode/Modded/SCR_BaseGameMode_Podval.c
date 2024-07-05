class MissionsConfig : JsonApiStruct
{
	ref array<string> missions;
	
	void MissionsConfig()
	{
		RegV("missions");
	}
}


modded class SCR_BaseGameMode
{	
	private string GetNextScenario()
	{
		MissionsConfig config = new MissionsConfig();
		config.LoadFromFile("$profile:Missions_Config.json");
		
		array<string> missions = config.missions;
		
		if(missions == null) {
			Print("Missions array has NULL", LogLevel.ERROR);
			return "";
		}
		
		int countMissions = missions.Count();
		
		if(countMissions <= 0) {
			return "";
		}
		
		SCR_MissionHeader missionHeader = SCR_MissionHeader.Cast(GetGame().GetMissionHeader());
		
		int currentMissionIndex = missions.Find(missionHeader.GetHeaderResourceName());
		
		if(currentMissionIndex >= 0) {
			int nextMissionIndex = currentMissionIndex + 1;
			
			if(nextMissionIndex > (countMissions - 1)) {
				nextMissionIndex = 0;
			}
	
			PrintFormat("Next mission index = %1", nextMissionIndex);
					
			return missions[nextMissionIndex];
		}
		
		PrintFormat("Current mission index = %1", currentMissionIndex);
		return "";
	}
	
	override protected void RestartSession()
	{
		if (!IsMaster()) {
			return;
		}
		
		Print("Start change scenario", LogLevel.NORMAL);
		
		string nextScenario = GetNextScenario();
		
		if(nextScenario.Length() <= 0) {
			Print("Close server if not selected next scenario", LogLevel.WARNING);
			GetGame().RequestClose();
			return;
		}
		
		PrintFormat("Scenario selected, change to: %1", nextScenario);
		
		GameStateTransitions.RequestScenarioChangeTransition(nextScenario, "");
	}
}