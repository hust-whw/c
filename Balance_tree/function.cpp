#include "head.h"

#define LH +1	
#define EH 0	
#define RH -1	

void print(PNode root)     //中序遍历AVL树，结果直接为升序数字

{
	if(root==NULL){
		return;
	}
	
	print(root->left);
	printf("%d  ",root->key);
	print(root->right);
}


PNode search(PNode root,int key)         //查找,找到返回关键字的结点指针，没找到返回NULL
{  
    if(root == NULL)  
        return NULL;  
    if(key > root->key) 
        return search(root->right,key);  
    else if(key < root->key)  
        return search(root->left,key);  
    else  
        return root;  
}  


PNode searchMin(PNode root)     //求最小值
{  
    if(root == NULL)  
        return NULL;  
    if(root->left == NULL)  
        return root;  
    else   
        return searchMin(root->left);  
}  


PNode searchMax(PNode root)     //求最大值
{  
    if(root == NULL)  
        return NULL;  
    if(root->right == NULL)  
        return root;  
    else   
        return searchMax(root->right);  
}  



void R_Rotate(PNode *p)    //右旋
{
	PNode lc;
	lc=(*p)->left; 
	(*p)->left=lc->right;  
	lc->right=*p;
	*p=lc;  
}


void L_Rotate(PNode *p)      //左旋
{
	PNode rc;
	rc=(*p)->right;  
	(*p)->right=rc->left; 
	rc->left=*p;
	*p=rc;  
}


void LeftBalance(PNode *root)   //插入节点在最小不平衡树的左子树中
{	
	PNode lc,rd;
	lc=(*root)->left;
	switch(lc->bf)
	{  
	case LH:  
		(*root)->bf=lc->bf=EH;
		R_Rotate(root);
		break;
	case RH:  
		rd=lc->right; 
		switch(rd->bf)
		{ 
		case LH:
			(*root)->bf=RH;
			lc->bf=EH;
			break;
		case EH: 
			(*root)->bf=lc->bf=EH;
			break;
		case RH:
			(*root)->bf=EH;
			lc->bf=LH;
		}
		rd->bf=EH;
		L_Rotate(&(*root)->left);  
		R_Rotate(root);
	}
}


void RightBalance(PNode *root)      //插入节点在最小不平衡树的右子树中
{
	PNode rc,rd;
	rc=(*root)->right; 
	switch(rc->bf)
	{ 
	case RH:  
		(*root)->bf=rc->bf=EH;
		L_Rotate(root);
		break;
	case LH:  
		rd=rc->left;  
		switch(rd->bf)
		{  
		case RH: (*root)->bf=LH;
			rc->bf=EH;
			break;
		case EH: (*root)->bf=rc->bf=EH;
			break;
		case LH: (*root)->bf=EH;
			rc->bf=RH;
		}
		rd->bf=EH;
		R_Rotate(&(*root)->right); 
		L_Rotate(root);  
	}
}


int InsertAVL(PNode *root,int e,int *taller)
{
	if(!*root)
	{ 
		*root=(PNode)malloc(sizeof(Node));
		(*root)->key=e;
		(*root)->left=(*root)->right=NULL;
		(*root)->bf=EH;
		*taller=1;
	}
	else
	{
		if(e == (*root)->key)
		{ 
			*taller=0;
			return 0;
		}
		if(e < (*root)->key)
		{  
			if(!InsertAVL(&(*root)->left,e,taller))  
				return 0;
			if(*taller)
				
				switch((*root)->bf) 
			{
				case LH:
					
					LeftBalance(root);
					*taller=0;
					break;
				case EH:
					
					(*root)->bf=LH;
					*taller=1;
					break;
				case RH:
					
					(*root)->bf=EH; 
					*taller=0;	
			}
		}
		else
		{
			
			if(!InsertAVL(&(*root)->right,e,taller)) 
				return 0;
			if(*taller)  
				switch((*root)->bf)         //通过taller和平衡因数bf来找到最小不平衡树的根节点，并调用旋转函数进行旋转。
			{
           case LH: 
			   (*root)->bf=EH;
			   *taller=0;
			   break;
           case EH: 
			   (*root)->bf=RH;
			   *taller=1;
			   break;
		   case RH:  
			   RightBalance(root);
			   *taller=0;
			}
		}
	}
	return 1;
}


void PrintTree(PNode root,int nlayer)    //横向打印树形
{
	int i;
	if(root==NULL) { 
		return ; 
	} 
	PrintTree( root->right,nlayer+3);
	for(i=0;i<nlayer;i++)
	{
		printf(" "); 
	}
	
	printf("%d\n",root->key);
	PrintTree(root->left,nlayer+3);
}


int create(PNode* root)     //连续输入建立AVL树
{  
    int key,i,k;   
    for(i=0;;i++) 
	{
		scanf("%d",&key);
		if(key==0)return i;
        InsertAVL(root,key,&k);
		printf("____________________________________________\n");
		PrintTree(*root,0);
		printf("____________________________________________\n");
	}
} 


bool Delete(int elem,PNode& root)
{
	bool flag,flagl,flagr,is_right=0,is_left=0;
	PNode temp = (PNode)malloc(sizeof(Node));
	PNode p = (PNode)malloc(sizeof(Node));
	if(root == NULL) return false;
	else
	{
		if(root->key == elem)
		{
			if(root->left!=NULL)
			{
				temp = root->left;
				p = root;
				while((temp)->right!=NULL)
				{	
				p = temp;
				temp = temp->right;
				is_right = 1;
				}
				if(temp->left == NULL)
				{
					root->key = temp->key;
					if(is_right == 1)
					{
						p->right = NULL;
						temp = NULL;
					}
					else 
					{
						p->left = NULL;
						temp = NULL;
					}
					
				}
				else
				{
					printf("heheheh");
					root->key = temp ->key;
					p = temp->left;
					temp->key = p->key;
					temp->left = p->left;
					temp->right = p->right;
				}
			}
			else 
			{
				
				if(root->right==NULL)
				{
					root = NULL;
					delete(root);
				}
				else
				{
					temp = root->right;
					p = root;

					while(temp->left!=NULL)
					{
						p = temp;
						temp = temp->left;
						is_left = 1;
					}
					if(temp->right == NULL)
					{
						root->key = temp->key;
					if(is_left == 1)
					{
						p->left = NULL;
						temp = NULL;
					}
					else 
					{
						p->right = NULL;
						temp = NULL;
					}
					}
					else
					{
						printf("hahaha");
						root->key = temp ->key;
						p = temp->right;
						temp->key = p->key;
						temp->left = p->left;
						temp->right = p->right;
					}
				}
			}
			return true;
		}
		else
		{
			flagl = Delete(elem,root->left);
			flagr = Delete(elem,root->right);
			flag = flagl | flagr;
		}
	}
	delete(temp);
	delete(p);
	return flag;
}


int Hight(PNode root)
{
	int left,right;
	if(root == NULL)
		return 0;
	else{
		left = 1 + Hight(root->left);
		right = 1 + Hight(root->right);
		
		if(left>right)
		{
			return left;
		}
		else
		{
			return right;
		}
	}
}


int ReBf(PNode& root)
{
	if(root==NULL)
	{
		return 0;
	}
	root->bf = Hight(root->left)-Hight(root->right);
	ReBf(root->left);
	ReBf(root->right); 
	return 1;
}


void AdjustBiTreeByLL(PNode& root)
{
	PNode lc = (PNode)malloc(sizeof(Node));
	lc=root->left;
	root->left=lc->right;
	lc->right=root; 
	root=lc;        
}


void AdjustBiTreeByRR(PNode& root)
{
	PNode lc = (PNode)malloc(sizeof(Node));
	lc=root->right;               
	root->right=lc->left;    
	lc->left=root;            
	root=lc;                                 
}


void AdjustBiTreeByLR(PNode& root)
{
	PNode b = (PNode)malloc(sizeof(Node));
	PNode c = (PNode)malloc(sizeof(Node));
	b = root->left;
	c = root->left->right;
	root->left=c->right;    
	b->right=c->left;  
	c->left=b;                
	c->right=root;            
	root = c;
}


void AdjustBiTreeByRL(PNode& root)
{
	PNode b = (PNode)malloc(sizeof(Node));
	PNode c = (PNode)malloc(sizeof(Node));
	
	b = root->right;
	c = root->right->left;
	
	root->right=c->left;    
	b->left=c->right;  
	c->right=b;                
	c->left=root;            
	root = c;
}


void AdjustAVLBiTree(PNode& root)
{
	int bf,lbf,rbf;
	if(root == NULL)return;
	bf = Hight(root->left) - Hight(root->right);
	if(bf == NULL) return;
	if(bf==2)
	{
		lbf = Hight(root->left->left) - Hight(root->left->right);
		//LL型变换
		if(lbf>=1){
			AdjustBiTreeByLL(root);
		}
		//LR型变换
		else if(lbf<=1){
			AdjustBiTreeByLR(root);
		}
	}else if(bf==-2)
	{
		
		rbf = Hight(root->right->left) - Hight(root->right->right);
		//RL型变换
		if(rbf>=1)
		{
			AdjustBiTreeByRL(root);
		}
		//RR型变换
		else if(rbf<=-1)
		{
			AdjustBiTreeByRR(root);
		}
	}
	else{
		if((root->left==NULL)&&(root->right==NULL)) 
		{
			return;
		}
		else{
			if(root->left !=NULL){
				AdjustAVLBiTree(root->left);
			}
			if(root->right !=NULL){
				AdjustAVLBiTree(root->right);
			}
		}
	}
}