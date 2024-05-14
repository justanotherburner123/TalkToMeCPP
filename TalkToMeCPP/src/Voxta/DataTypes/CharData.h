// Copyright(c) 2024 grrimgrriefer & DZnnah, see LICENSE for details.

#pragma once
#include <string>
#include <memory>

namespace Voxta::DataTypes
{
	struct CharData
	{
		explicit CharData(std::string_view id, std::string_view name) : m_id(id), m_name(name) {}
		~CharData() = default;

		std::string m_id;
		std::string m_name;
		std::string m_creatorNotes = "";
		bool m_explicitContent = false;
		bool m_favorite = false;
	};

	struct CharDataIdComparer
	{
		std::string_view m_charId;
		explicit CharDataIdComparer(std::string_view charId) : m_charId(charId) {}

		bool operator()(const std::unique_ptr<DataTypes::CharData>& element) const
		{
			return element->m_id == m_charId;
		}

		bool operator()(const std::unique_ptr<const DataTypes::CharData>& element) const
		{
			return element->m_id == m_charId;
		}
	};
}