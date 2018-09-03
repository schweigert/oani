/**
   \file PoseAttr.h
   \brief Descricao da classe PoseAttr

   Esta classe tem por objetivo implementar a descrição de um atribulo interpolável para uma animação pose-to-pose

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _POSEATTR_NOT_INCLUDED_
#define _POSEATTR_NOT_INCLUDED_

#include "Vector3.h"

class Entity;

/**
   \class PoseAttr
   \brief Classe abstrata para definição de um atributo interpolável
*/
class PoseAttr
{
public:
	/**
	\brief Lista de possiveis atributos suportados
	*/
	enum AttrName {
		TRANSLATE = 0,  ///< aplica os valores no componente de translação do Entity
		ROTATE,         ///< aplica os valores no componente de rotação do Entity
		ROTATE_PIVOT,   ///< aplica os valores no componente de rotação em relação do pivot do Entity
		SCALE           ///< aplica os valores no componente de escala do Entity
	};

protected:
    PoseAttr::AttrName attrName;  ///< nome do atributo interpolavel
    double             dAttrTime; ///< tempo (em segundos) na timeline para este atributo interpolável

public:
    PoseAttr( double, PoseAttr::AttrName );
    PoseAttr( PoseAttr * );

    void setTime( double );
    /**
    \brief Retorna o valor do tempo do atributo interpolavel
    \return valor (em segundos) do tempo do atributo interpolavel
    */
    inline double getTime() { return this->dAttrTime; }

    /**
    \brief Retorna o nome do atributo interpolavel
    \return nome do atributo interpolavel (uma das constantes do enum)
    */
    inline PoseAttr::AttrName getName() { return this->attrName; }

    virtual void updateParent( Entity * ) = 0;
};

#endif
