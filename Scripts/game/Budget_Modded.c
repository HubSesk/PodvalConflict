modded class SCR_EntityBudgetValue
{
	override void SetBudgetValue(int newValue)
	{
		m_Value = 0;
	}
	
	override bool AddBudgetValue(SCR_EntityBudgetValue entityBudgetValue)
	{
		if (entityBudgetValue.GetBudgetType() == GetBudgetType())
		{
			m_Value = 0;
			return true;
		}
		return false;
	}
	
	override static void MergeBudgetCosts(out notnull array<ref SCR_EntityBudgetValue> outExistingBudgets, array<ref SCR_EntityBudgetValue> newBudgetCosts)
	{
		foreach (SCR_EntityBudgetValue newBudgetCost : newBudgetCosts)
		{
			bool budgetExists = false;
			foreach (SCR_EntityBudgetValue existingBudget : outExistingBudgets)
			{
				if (existingBudget.AddBudgetValue(newBudgetCost))
				{
					budgetExists = true;
					break;
				}
			}
			if (!budgetExists)
			{
				//outExistingBudgets.Insert(newBudgetCost);
			}
		}
	}

	override static void AddBudgetValueToBudgetArray(out notnull array<ref SCR_EntityBudgetValue> budgets, EEditableEntityBudget budgetType, int value)
	{
		foreach (SCR_EntityBudgetValue budgetValue : budgets)
		{
			if (budgetValue.GetBudgetType() == budgetType)
			{
				//budgetValue.SetBudgetValue(budgetValue.GetBudgetValue() + value);
				return;
			}
		}
		
		budgets.Insert(new SCR_EntityBudgetValue(budgetType, value));
	}
}