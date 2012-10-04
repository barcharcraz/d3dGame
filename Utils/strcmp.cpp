namespace scratch {
	int strcmp(const char *s1, const char *s2) {
		int retVal = 0;
		retVal = *s1 - *s2;
		if(retVal != 0) {
			return retVal;
		}
		if(*s1 && *s2) {
			strcmp(s1+1, s2+1);
		}
		return retVal;
	}
};