#ifndef CONTACTLISTENER_H
#define	CONTACTLISTENER_H

#include <Box2D\Box2D.h>

class ContactListener : public b2ContactListener {
	public:
		ContactListener() : numFootContacts(0) {}
		void BeginContact(b2Contact* contact) {
			//check if fixture A was the foot sensor
			void* fixtureUserData = contact->GetFixtureA()->GetUserData();
			if ( (int)fixtureUserData == 3 )
				numFootContacts++;
			//check if fixture B was the foot sensor
			fixtureUserData = contact->GetFixtureB()->GetUserData();
			if ( (int)fixtureUserData == 3 )
			numFootContacts++;
		}
  
		void EndContact(b2Contact* contact) {
			//check if fixture A was the foot sensor
			void* fixtureUserData = contact->GetFixtureA()->GetUserData();
			if ( (int)fixtureUserData == 3 )
				numFootContacts--;
			//check if fixture B was the foot sensor
			fixtureUserData = contact->GetFixtureB()->GetUserData();
			if ( (int)fixtureUserData == 3 )
				numFootContacts--;
		}
		int numFootContacts;
};

#endif CONTACTLISTENER_H