<<<<<<< HEAD
#pragma once
#include "../../General_Heading.h"


// ÏÅĞÅ×ÈÑËÅÍÈÅ ÄËß ÎÏĞÅÄÅËÅÍÈß ĞÅÆÈÌÀ ÔÈËÜÒĞÀÖÈÈ
enum class TextureFilter {
	POINT, // ÒÎ×Å×ÍÀß
	BILINEAR, // ÁÈËÈÍÅÉÍÀß
	TRILINEAR, // ÒĞÈËÈÍÅÉÍÀß
	ANISOTROPIC // ÀÍÈÇÒÎĞÎÏÍÀß
};
// ÊËÀÑÑ ÄËß ĞÀÁÎÒÛ Ñ ÒÅÊÑÒÓĞÎÉ
class Texture
{
public:
	// çàãğóçêà òåêñòóğû èç âíåøíåãî ôàéëà
	void load(std::string filename);

	// ïğèìåíåíèå òåêñòóğû (ïğèâçÿêà ê òåêñòóğíîìó áëîêó è óñòàíîâêà ïàğàìåòğîâ)
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);
	// îòêëş÷åíèå òåêñòóğèğîâàíèÿ äëÿ âñåõ òåêñòóğíûõ áëîêîâ
	static void disableAll();
private:
	// èäåíòèôèêàòîğ (èíäåêñ) òåêñòóğíîãî îáúåêòà
	GLuint texIndex;
=======
#pragma once
#include "../../General_Heading.h"


// ÏÅĞÅ×ÈÑËÅÍÈÅ ÄËß ÎÏĞÅÄÅËÅÍÈß ĞÅÆÈÌÀ ÔÈËÜÒĞÀÖÈÈ
enum class TextureFilter {
	POINT, // ÒÎ×Å×ÍÀß
	BILINEAR, // ÁÈËÈÍÅÉÍÀß
	TRILINEAR, // ÒĞÈËÈÍÅÉÍÀß
	ANISOTROPIC // ÀÍÈÇÒÎĞÎÏÍÀß
};
// ÊËÀÑÑ ÄËß ĞÀÁÎÒÛ Ñ ÒÅÊÑÒÓĞÎÉ
class Texture
{
public:
	// çàãğóçêà òåêñòóğû èç âíåøíåãî ôàéëà
	void load(std::string filename);

	// ïğèìåíåíèå òåêñòóğû (ïğèâçÿêà ê òåêñòóğíîìó áëîêó è óñòàíîâêà ïàğàìåòğîâ)
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);
	// îòêëş÷åíèå òåêñòóğèğîâàíèÿ äëÿ âñåõ òåêñòóğíûõ áëîêîâ
	static void disableAll();
private:
	// èäåíòèôèêàòîğ (èíäåêñ) òåêñòóğíîãî îáúåêòà
	GLuint texIndex;
>>>>>>> 1f562be79d16193a9746e34b908252d6844f6415
};