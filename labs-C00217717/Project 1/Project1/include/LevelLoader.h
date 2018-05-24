/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>
#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "yaml-cpp\yaml.h"

/// <summary>
/// A struct to represent the Paddle Data in Yaml
/// </summary>
struct PaddleData
{
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	float m_moveSpeed;
};

/// <summary>
/// A struct to represent the ball Data in Yaml
/// </summary>
struct BallData
{
	sf::Vector2f m_position;
	bool m_shown;
};

/// <summary>
/// A struct to represent the Enemy Data in Yaml
/// </summary>
struct EnemyData
{
	std::string m_type;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	bool m_shown;
};

/// <summary>
/// A struct to represent the Brick Data in Yaml
/// </summary>
struct BrickData
{
	std::string m_type;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	bool m_shown;
};

/// <summary>
/// A struct representing all the Level Data.
/// 
/// Enemies and Bricks are repeasted so are stored in a Vector
/// </summary>
struct LevelData
{
	PaddleData m_paddle;
	BallData m_ball;
	std::vector<EnemyData> m_enemies;
	std::vector<BrickData> m_bricks;
};

/// <summary>
/// A class to manage level loading.
/// 
/// This class will manage level loading using YAML.
/// </summary>
class LevelLoader
{
public:

	/// <summary>
	/// @brief No-op default constructor.
	/// 
	/// </summary>
	LevelLoader() = default;

	/// <summary>
	/// @brief Loads and parses the yaml level file.
	/// The level file is identified by a number and is assumed to have
	/// the following format: "level" followed by number followed by .yaml extension
	/// E.g. "level1.yaml"
	/// The level information is stored in the specified LevelData object.
	/// If the filename is not found or the file data is invalid, an exception
	/// is thrown.
	/// </summary>
	/// <param name="nr">The level number</param>
	/// <param name="level">A reference to the LevelData object</param>
	static bool load(int nr, LevelData& level);
};