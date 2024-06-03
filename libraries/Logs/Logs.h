#ifndef Logs_h
#define Logs_h

class Logs{
	private:
		bool _enable = false;
	public:
		char msg[50];
		void log(char *msg);
		void log();
		void setActive(bool active);
		bool isActive();
};

#endif