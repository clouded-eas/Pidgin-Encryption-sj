#ifndef G_GNUC_NULL_TERMINATED
#	if     __GNUC__ >= 4
#		define G_GNUC_NULL_TERMINATED __attribute__((__sentinel__))
#	else
#		define G_GNUC_NULL_TERMINATED
#	endif
#endif
