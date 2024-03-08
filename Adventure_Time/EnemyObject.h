#ifndef ENEMYMODEL_H_
#define ENEMYMODEL_H_
#include "ObjectModel.h"

class EnemyObject :
    public ObjectModel
{
public:
	EnemyObject();
	~EnemyObject();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();
};

#endif

