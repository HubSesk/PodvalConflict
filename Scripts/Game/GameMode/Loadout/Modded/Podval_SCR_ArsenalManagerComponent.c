modded class SCR_ArsenalManagerComponent
{
	override protected bool CanSaveLoadout(int playerId, notnull GameEntity characterEntity, FactionAffiliationComponent playerFactionAffiliation, SCR_ArsenalComponent arsenalComponent, bool sendNotificationOnFailed)
	{
		if(!super.CanSaveLoadout(playerId, characterEntity, playerFactionAffiliation, arsenalComponent, sendNotificationOnFailed)) {
			return false;
		}
		
		if (!arsenalComponent || (arsenalComponent.GetArsenalSaveType() == SCR_EArsenalSaveType.NO_RESTRICTIONS && (!m_LoadoutSaveBlackListHolder || m_LoadoutSaveBlackListHolder.GetBlackListsCount() == 0))) {
			return false;
		}

		set<string> checkedEntities = new set<string>();
		
		EntityPrefabData prefabData;
		RplComponent itemRplComponent;
		string resourceName;
		
		int invalidItemCount = 0;
		
		array<Managed> inventories = {};
		characterEntity.FindComponents(InventoryStorageManagerComponent, inventories);
		
		array<BaseInventoryStorageComponent> storages = {};
		foreach (Managed inventory : inventories) {
		    InventoryStorageManagerComponent.Cast(inventory).GetStorages(storages);
		}
		
		array<IEntity> items = {};
		foreach (BaseInventoryStorageComponent storage : storages) {
		      storage.GetAll(items);
		}
		
		foreach (IEntity item : items) {
			prefabData = item.GetPrefabData();
			
			//~ Ignore if no prefab data
			if (!prefabData)
				continue;
			
			//~ Ignore if no prefab resource name
			resourceName = prefabData.GetPrefabName();
			if (resourceName.IsEmpty())
				continue;
			
			//~ Do not check the same item twice
			if (checkedEntities.Contains(resourceName))
				continue;
				
			checkedEntities.Insert(resourceName);
			
			if (m_LoadoutSaveBlackListHolder && m_LoadoutSaveBlackListHolder.GetBlackListsCount() != 0)
			{
				//~ Item is blackListed so do not allow saving
				if (m_LoadoutSaveBlackListHolder.IsPrefabBlacklisted(resourceName))
				{
					if (sendNotificationOnFailed)
					{
						itemRplComponent = RplComponent.Cast(item.FindComponent(RplComponent));
						if (itemRplComponent)
							SCR_NotificationsComponent.SendToPlayer(playerId, ENotification.PLAYER_LOADOUT_ITEM_FAILED_ITEM_BLACKLISTED, itemRplComponent.Id());
					}
				
					invalidItemCount++;
					continue;
				}
			}
		};
		
		//~ Saving failed because of invalid items
		if (invalidItemCount > 0 && sendNotificationOnFailed)
			SCR_NotificationsComponent.SendToPlayer(playerId, ENotification.PLAYER_LOADOUT_NOT_SAVED_INVALID_ITEMS, invalidItemCount);
		
		return invalidItemCount == 0;
	}
}
