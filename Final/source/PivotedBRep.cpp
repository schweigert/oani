#include "PivotedBRep.h"
#include "BRep.h"

/**
  \brief Construtor padrao para a classe PivotedBRep
  Cria um objeto PivotedBRep vazio
*/
PivotedBRep::PivotedBRep(): Pivot()
{}
/**
  \brief Construtor de clonagem para objetos da classe PivotedBRep
  Copia um objeto PivotedBRep
  \param Clone objeto da classe a ser copiado
*/
PivotedBRep::PivotedBRep( const PivotedBRep& Clone ): Pivot( Clone )
{}
/**
  \brief Construtor de clonagem para objetos da classe PivotedBRep a partir de ponteiros
  Copia um objeto PivotedBRep
  \param ptrClone ponteiro para o objeto da classe a ser copiado
*/
PivotedBRep::PivotedBRep( PivotedBRep* ptrClone ): Pivot( ptrClone )
{}
/**
  \brief Carrega um objeto BRep a partir de um arquivo e associa a um elemento Pivot
  \param strFileName nome do arquivo BRep (no formato Wavefront [*.obj]) a ser carregado
*/
void PivotedBRep::OnLoad( string strFileName )
{
	BRep * ptrNewBRep = new BRep();
	ptrNewBRep->LoadfromFile( strFileName );
	this->attach( ptrNewBRep );
}
/**
	\brief Rotina de atualizacao dos parametros animaveis do objeto.<p>
	Esta rotina deve ser sobrecarregada para cada tipo de entidade em particular.
*/
void PivotedBRep::OnLoop( double dDeltaTime )
{
	Pivot::OnLoop( dDeltaTime );
}
