#pragma once

#include "Pose.h"
#include <vector>
#include <string>

namespace animation {
	class Skeleton
	{
	public:
		Skeleton();
		Skeleton(const Pose& rest,const Pose& bind,const std::vector<std::string>& names);

		void Set(const Pose& rest,const Pose& bind,const std::vector<std::string>& names);

		Pose& GetBindPose();
		Pose& GetRestPose();
		std::vector<glm::mat4>& GetInvBindPose();
		std::vector<std::string>& GetJointNames();
		std::string& GetJointName(unsigned int index);
	protected:
		//
		Pose m_RestPose; // rest => 静止 => その瞬間でのアニメーションのポーズ(1コマ??)
		Pose m_BindPose; // bindPose => T-Pose のこと
		std::vector<glm::mat4> m_InvBindPose;
		std::vector<std::string> m_JointNames;

		//
		void UpdateInverseBindPose();
	};
}