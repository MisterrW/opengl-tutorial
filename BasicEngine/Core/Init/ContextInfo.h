namespace BasicEngine
{
	namespace Core {

		//OpenGL versions
		struct ContextInfo
		{
			int major_version, minor_version;
			bool core;

			ContextInfo()//default
			{
				major_version = 3;
				minor_version = 3;
				core = true;
			}

			ContextInfo(int major_version, int minor_version, bool core)
			{
				this->major_version = major_version;
				this->minor_version = minor_version;
				this->core = core;
			}

			//just like windowInfo.h
			//implement copy constructor
			//implement assignment operator
			//these implementations are optional because are special functions
			//http://en.wikipedia.org/wiki/Special_member_functions

			//copy constructor
			ContextInfo(ContextInfo& contextInfo) {
				this->major_version = contextInfo.major_version;
				this->minor_version = contextInfo.minor_version;
				this->core = contextInfo.core;
			}

			//operator equals
			void operator=(ContextInfo& contextInfo) {
				this->major_version = contextInfo.major_version;
				this->minor_version = contextInfo.minor_version;
				this->core = contextInfo.core;

			}
		};
	}
}