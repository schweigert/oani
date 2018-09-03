#ifndef _LIGHTSOURCE_H_
#define _LIGHTSOURCE_H_

#include "ColoredEntity.h"
// #include <Windows.h>
#include <GL/glut.h>

/**
\class LightSource
\brief Uma fonte de luz utilizada pelo processo de iluminacao de objetos na cena. Reutiliza os parametros de Entity e ColoredEntity
*/
class LightSource: public ColoredEntity
{
public:
	enum LightSourceType
	{
		POINT,       ///< luz pontual onde todos os raios de partem a partir de um unico ponto no espaco
		DIRECTIONAL, ///< luz direcional onde todos os raios de luz sao paralelos partindo do infinito
		SPOTLIGHT    ///< feixe de luz direcional partindo de um dado ponto, em uma dada direcao com um certo angulo de abertura
	};

private:
	GLenum          lightENUM;             ///< indice da fonte de luz no OPENGL
	unsigned int    iLightSourceIndex;     ///< atributo de classe que determina o indice dessa fonte de luz para o OPENGL
	LightSourceType Type;                  ///< tipo da fonte de luz
	Vector3         vAmbientColor,         ///< definicao da cor ambiente da fonte de luz
		            vSpecularColor,        ///< definicao da cor especular da fonte de luz
			        vDirection;            ///< direcao do eixo principal do feixe de luz
	float           fExponent,             ///< expoente usado no calculo da luz spot
			        fCuttOff,              ///< angulo de abertura do feixe de luz spot
			        fConstantAttenuation,  ///< fator de atenuacao da luz pela distancia de forma constante
			        fLinearAttenuation,    ///< fator de atenuacao da luz pela distancia de forma linear
			        fQuadraticAttenuation; ///< fator de atenuacao da luz pela distancia de forma quadratica
	bool            bActive;               ///< flag que indica se a luz esta ligada ou nao

public:
	LightSource( unsigned int, LightSource::LightSourceType = LightSource::POINT );
	LightSource( unsigned int, const LightSource& );
	LightSource( unsigned int, LightSource* );

	void setAmbientColor( Vector3 );
	/**
	  \brief Retorna o valor corrente da constante de iluminacao ambiente. Luz ambiente denota a cor dos pontos de luz indireta (aqueles nao iluminados pela fonte de luz)
	  \return cor da iluminacao ambiente corrente
	*/
	inline Vector3 getAmbientColor() { return this->vAmbientColor; }

	void setSpecularColor( Vector3 );
	/**
	  \brief Retorna o valor corrente da constante de iluminacao especular. Luz especular denota a cor do brilho das superficies reflexivas (polidas)
	  \return cor da iluminacao especular corrente
	*/
	inline Vector3 getSpecularColor() { return this->vSpecularColor; }

	void setDirection( Vector3 );
	/**
	  \brief Retorna o valor corrente da direcao de iluminacao do feixe de luz. E desconsiderado para luzes pontuais.
	  \return direcao do eixo principal do feixe de luz
	*/
	inline Vector3 getDirection() { return this->vDirection; }

	void setExponent( float );
	/**
	  \brief Retorna o valor corrente da constante expoente usada no calculo de iluminacao spot.
	  \return valor corrente do expoente de iluminacao spot
	*/
	inline float getExponent() { return this->fExponent; }

	void setCutOff( float );
	/**
	  \brief Retorna o valor corrente do angulo de abertura do feixe de iluminacao spot
	  \return angulo de abertura do feixe spot
	*/
	inline float getCutOff() { return this->fCuttOff; }

	void setConstantAttenuation( float );
	/**
	  \brief Retorna o valor corrente da constante de atenuacao da luz pela distancia de forma constante
	  \return constante de atenuacao da luz
	*/
	inline float getConstantAttenuation() { return this->fConstantAttenuation; }

	void setLinearAttenuation( float );
	/**
	  \brief Retorna o valor corrente da constante de atenuacao da luz pela distancia de forma linear
	  \return constante de atenuacao da luz
	*/
	inline float getLinearAttenuation() { return this->fLinearAttenuation; }

	void setQuadraticAttenuation( float );
	/**
	  \brief Retorna o valor corrente da constante de atenuacao da luz pela distancia de forma quadratica
	  \return constante de atenuacao da luz
	*/
	inline float getQuadraticAttenuation() { return this->fQuadraticAttenuation; }

	void OnRender();
	void Activate();

	void OnLoop( double );
};

#endif
