/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>

#include "LevelLoader.h"

/// <summary>
/// Extracts the paddle position, Size and Speed values.
/// 
/// </summary>
/// <param name="t_paddleNode">A YAML node</param>
/// <param name="t_paddle">A simple struct to store the Paddle data</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& t_paddleNode, PaddleData& t_paddle)
{	
	t_paddle.m_position.x = t_paddleNode["position"]["x"].as<float>();
	t_paddle.m_position.y = t_paddleNode["position"]["y"].as<float>();

	t_paddle.m_size.x = t_paddleNode["size"]["x"].as<float>();
	t_paddle.m_size.y = t_paddleNode["size"]["y"].as<float>();

	t_paddle.m_moveSpeed = t_paddleNode["speed"].as<float>();
}

void operator >> (const YAML::Node& t_ballNode, BallData& t_ball)
{
	t_ball.m_position.x = t_ballNode["position"]["x"].as<float>();
	t_ball.m_position.y = t_ballNode["position"]["y"].as<float>();

	t_ball.m_shown = t_ballNode["shown"].as<bool>();
}

void operator >> (const YAML::Node& t_enemyNode, EnemyData& t_enemy)
{
	t_enemy.m_type = t_enemyNode["type"].as<std::string>();
	
	t_enemy.m_position.x = t_enemyNode["position"]["x"].as<float>();
	t_enemy.m_position.y = t_enemyNode["position"]["y"].as<float>();

	t_enemy.m_size.x = t_enemyNode["size"]["x"].as<float>();
	t_enemy.m_size.y = t_enemyNode["size"]["y"].as<float>();

	t_enemy.m_shown = t_enemyNode["shown"].as<bool>();
}

void operator >> (const YAML::Node& t_brickNode, BrickData& t_brick)
{
	t_brick.m_type = t_brickNode["type"].as<std::string>();

	t_brick.m_position.x = t_brickNode["position"]["x"].as<float>();
	t_brick.m_position.y = t_brickNode["position"]["y"].as<float>();

	t_brick.m_size.x = t_brickNode["size"]["x"].as<float>();
	t_brick.m_size.y = t_brickNode["size"]["y"].as<float>();

	t_brick.m_shown = t_brickNode["shown"].as<bool>();
}


/// <summary>
/// @brief Top level function that extracts various game data from the YAML data stucture.
/// 
/// </summary>
/// <param name="levelNode">A YAML node</param>
/// <param name="level">A simple struct to store data related to the level </param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& levelNode, LevelData& level)
{
	levelNode["paddle"] >> level.m_paddle;

	levelNode["ball"] >> level.m_ball;
		
	const YAML::Node& enemyNode= levelNode["enemies"].as<YAML::Node>();
	for (unsigned i = 0; i < enemyNode.size(); ++i)
		{
		EnemyData enemy;
		enemyNode[i] >> enemy;
		level.m_enemies.push_back(enemy);
	}

	const YAML::Node& brickNode = levelNode["bricks"].as<YAML::Node>();
	for (unsigned i = 0; i < brickNode.size(); ++i)
	{
		BrickData brick;
		brickNode[i] >> brick;
		level.m_bricks.push_back(brick);
	}
}

////////////////////////////////////////////////////////////
bool LevelLoader::load(int nr, LevelData& level)
{
	std::stringstream ss;
	ss << "resources//levels//level";
	ss << nr;
	ss << ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(ss.str());
		if (baseNode.IsNull())
		{
			std::string message("file: " + ss.str() + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> level;
	}
	catch (YAML::ParserException& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}

