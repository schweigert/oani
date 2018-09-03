/**
   \file ColoredEntity.h
   \brief Descricao da classe ColoredEntity

   Esta classe representa todos os elementos do framework que apresentam o atributo fisico de cor.<br>

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Agosto, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _COLORED_ENTITY_H_
#define _COLORED_ENTITY_H_

#include "Entity.h"

/**
   \class ColoredEntity
   \brief Classe que tem por objetivo agrupar todos os elementos fisicos com cor do framework. E uma especializacao para a classe entidade.
   \sa Entity()
*/
class ColoredEntity: public Entity
{
protected:
     Vector3 vColor; ///< cor do objeto padrao RGBA

public:
	  ColoredEntity();
	  ColoredEntity( const ColoredEntity& );
	  ColoredEntity( ColoredEntity* );

	  void setColor( const Vector3 );
		/**
		  \brief Retorna o valor corrente da cor do objeto
		  \return Vector3 com o valor atual do vetor cor
		*/
	   inline Vector3 getColor() { return this->vColor; }

	  virtual void OnLoop( double );
};

#endif
