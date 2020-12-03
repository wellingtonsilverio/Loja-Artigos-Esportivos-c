
//EXEMPLO DE POSSIVEL EXCLUSAO:
//excluirEstoque: recebe a lista de produtos e o codigo a ser removido, busca e remove da lista.
void excluirEstoque(estoque **lista, int deleteCode){
  estoque *p = (*lista);
  estoque *anterior = NULL;
  int deleted = 0;
  
  //acho que podemos usar o "getNext" que vc criou ao inves de p->prox.
  while((p!=NULL)&&(deleted==0)){
  	if(p->codigo==deleteCode){
		if(anterior==NULL){                 //Primeiro item da Lista
			(*lista)=(*lista)->prox;		
			p->codigo=0;
		}else if(p->prox==NULL){           //Ultimo item da Lista
  			anterior->prox = NULL;
  			p->codigo=0;
  		}else{                            //No meio da Lista
			anterior->prox = p->prox;
			p->codigo=0;
		}
		free(p);
		deleted=1;
	}else{
		anterior = p;
	}
    p = p->prox;
  }
}
