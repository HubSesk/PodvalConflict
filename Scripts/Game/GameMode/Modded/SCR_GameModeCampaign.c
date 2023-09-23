modded class SCR_GameModeCampaign
{
	override void OnWorldPostProcess(World world)
	{
		super.m_bAutostart = false;
		super.OnWorldPostProcess(world);
	}
}