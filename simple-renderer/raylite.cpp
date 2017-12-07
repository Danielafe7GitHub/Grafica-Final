#include "renderer/engine.h"

//! main entry point
int main(int __argc,char **__argv)
{
	// the rendering engine
	engine _rendering_engine("./data/test-cubo.scn");

	// run the engine
	return _rendering_engine.run();
}
