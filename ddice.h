enum target {
	SNARE = 38,
	HIHAT = 42,
	KICK = 36,
	NONE,
};

struct tick {
	enum target 	lhand;
	enum target 	rhand;
	enum target 	rfoot;
};
/*
38 Acoustic Snare
35 Acoustic Bass Drum
36 Bass Drum 1
42 Closed Hi Hat
	int 		midi_note = 76;	* 76 77  low, high wood block *
*/

struct tick    *make_tick();
void 		zero_tick(struct tick *);
enum target 	rand_rfoot_1();
enum target 	rand_lhand_1();
void 		play_tick(PortMidiStream *, struct tick *);
