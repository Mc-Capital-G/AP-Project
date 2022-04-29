#include "bullet.h"
#include "enums.h"

bullet::bullet(int bulletType) {
	type = bulletType;
	switch (type) {
	case NORMAL || ENEMY:
		dmg = 1;
		speed = 10;
		break;
	case BOMB:
		dmg = 5;
		speed = 5;
		break;
	}
}