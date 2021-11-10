#pragma once

#include <JZEngine.h>
#include <string>
#include <sstream>
#include "../ButtonLogic.h"

enum class CutSceneState
{
	CutScene,
	Skip
};

enum class MessageOrder
{
	Nothing,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten
};

CutSceneState current_cut_scene_state = CutSceneState::CutScene;
MessageOrder message_order = MessageOrder::Nothing;
bool Message1st{false};
bool Message2nd{false};

//template <typename...T>
//void FirstMsg(T...text)
//{
//	std::stringstream ss;
//	((ss << text), ...);
//	Scene().GetComponent<JZEngine::TextData>("1st_msg_text")->text = JZEngine::String(ss.str().c_str());
//}

void Flag1stMsg(bool flag)
{
	// active/inactive 1st msg
	Scene().EntityFlagActive("1st_msg_bg", flag);
	Scene().EntityFlagActive("1st_msg_emoji", flag);
	Scene().EntityFlagActive("1st_msg_text", flag);
}

void Flag2ndMsg(bool flag)
{
	Scene().EntityFlagActive("2nd_msg_bg", flag);
	Scene().EntityFlagActive("2nd_msg_emoji", flag);
	Scene().EntityFlagActive("2nd_msg_text", flag);
}

bool CheckMessageOrder(MessageOrder order)
{
	return order == message_order;
}

void CutSceneInit()
{
	current_cut_scene_state = CutSceneState::CutScene;
	message_order = MessageOrder::Nothing;
	Flag1stMsg(false);
	Flag2ndMsg(false);
	Scene().GetComponent<JZEngine::TextData>("1st_msg_text")->text = JZEngine::String("Baozi, are you still up?");
	Scene().GetComponent<JZEngine::TextData>("2nd_msg_text")->text = JZEngine::String("Yea, what’s up?");
	Scene().GetComponent<JZEngine::TextData>("2nd_msg_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	//FirstMsg("Baozi, are you still up?");
	
}

void CutSceneUpdate(float dt)
{
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Phone_app_bg"))
	{
		if (e->on_click_)
		{
			if (CheckMessageOrder(MessageOrder::Nothing))
			{
				Flag1stMsg(true);
				message_order = MessageOrder::One;
			}
			if (CheckMessageOrder(MessageOrder::One))
			{
				Flag2ndMsg(true);
				message_order = MessageOrder::Two;
			}
			
			
		}
	}
	
}
