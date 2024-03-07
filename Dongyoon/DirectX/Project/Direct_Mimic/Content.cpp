#include "pch.h"
#include "Content.h"

#include <Engine/CAssetMgr.h>

#include "TreeUI.h"

Content::Content()
	: UI("Content", "##Content")
{
	// ContentUI 자식으로 Tree 를 지정
	m_Tree = new TreeUI("ContentTree");
	m_Tree->ShowRootNode(false);
	AddChildUI(m_Tree);

	// Tree 구성
	TreeNode* pNode = m_Tree->AddTreeNode(nullptr, "RootNode", 0);

	m_Tree->AddTreeNode(pNode, "Child1", 0);
	m_Tree->AddTreeNode(pNode, "Child2", 0);
	pNode = m_Tree->AddTreeNode(pNode, "Child3", 0);

	m_Tree->AddTreeNode(pNode, "Child3-1", 0);
	m_Tree->AddTreeNode(pNode, "Child3-2", 0);

	ResetContent();
}

Content::~Content()
{
}

void Content::render_update()
{
}

void Content::ResetContent()
{
	m_Tree->ClearNode();
	TreeNode* RootNode = m_Tree->AddTreeNode(nullptr, "Root", 0);

	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		TreeNode* CategoryNode = m_Tree->AddTreeNode(RootNode, ASSET_TYPE_STRING[i], 0);

		const map<wstring, Ptr<CAsset>>& mapAsset = CAssetMgr::GetInst()->GetAssets((ASSET_TYPE)i);
	
		for (const auto& pair : mapAsset)
		{
			m_Tree->AddTreeNode(CategoryNode, string(pair.first.begin(), pair.first.end()), (DWORD_PTR)pair.second.Get());
		}
	}
}

