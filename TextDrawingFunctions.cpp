#include <SDL.h>
#include <SDL_ttf.h>

#include "Tile.h"
#include "Constants.h"
#include "DrawingFunctions.h"

void renderTopMessage(SDL_Renderer *renderer, const std::string message, const SDL_Color color)
{
    SDL_Rect rect;
    rect.x = BOARD_STARTX;
    rect.y = 0;
    rect.w = BOARD_WIDTH_PIXELS;
    rect.h = BOARD_STARTY;

    renderTextToCenterOfRect(renderer, message, NORMAL_FONT_LINK, color, 20, rect);
}

void renderBottomMessage(SDL_Renderer *renderer, const std::string message, const SDL_Color color)
{
    SDL_Rect rect;
    rect.x = BOARD_STARTX;
    rect.y = BOARD_STARTY + BOARD_HEIGHT_PIXELS;
    rect.w = BOARD_WIDTH_PIXELS;
    rect.h = SCREEN_HEIGHT - rect.y;

    renderTextToCenterOfRect(renderer, message, NORMAL_FONT_LINK, color, 20, rect);
}

void renderPauseMessage(SDL_Renderer *renderer)
{

	SDL_Rect rect;
	rect.x = 0;
	rect.w = SCREEN_WIDTH;

	rect.y = 0;
	rect.h = SCREEN_HEIGHT / 2;
	renderImageToCenterOfRect(renderer, TETRIS_600x200_FILE, rect);

	rect.y += rect.h;
	rect.h = SCREEN_HEIGHT / 6;
	renderTextToCenterOfRect(renderer, "Game paused", NORMAL_FONT_LINK, WHITE_COLOR, 36, rect);

	rect.y += rect.h;
	rect.h = SCREEN_HEIGHT / 6;
	renderTextToCenterOfRect(renderer, "Press [P] to resume play", NORMAL_FONT_LINK, BLUE_COLOR, 36, rect);

}

void renderGameOverMessages(SDL_Renderer *renderer)
{
	SDL_Rect rect;
	rect.x = BOARD_STARTX;
	rect.y = BOARD_STARTY;
	rect.w = BOARD_WIDTH_PIXELS;
	rect.h = BOARD_HEIGHT_PIXELS;
	renderImageToCenterOfRect(renderer, GAMEOVER_FILE, rect);
	renderBottomMessage(renderer, "Press [R] to restart", LIME_COLOR);
}

void renderRemovedLinesMessage(SDL_Renderer *renderer, int numOfRemovedLines)
{
	std::string message = "";
	SDL_Color color = DEFAULT_COLOR;

	if (numOfRemovedLines == 1) {
		message = "SINGLE! (+40)";
		color = WHITE_COLOR;
	} else if (numOfRemovedLines == 2) {
		message = "DOUBLE! (+100)";
		color = YELLOW_COLOR;
	} else if (numOfRemovedLines == 3) {
		message = "TRIPLE! (+300)";
		color = RED_COLOR;
	} else if (numOfRemovedLines == 4) {
		message = "TETRIS! (+1200)";
		color = PURPLE_COLOR;
	}
	renderTopMessage(renderer, message, color);
}

void renderLevelUpMessage(SDL_Renderer* renderer)
{
	renderBottomMessage(renderer, "LEVEL UP!", ORANGE_COLOR) ;
}

void renderLeftMenu(SDL_Renderer* renderer, int score, int level, int removedLines, Tile &nextTile)
{
	SDL_Rect rect;
	rect.x = 0;
	rect.w = BOARD_STARTX;

	rect.y = 0;
	rect.h = SCREEN_HEIGHT / 3;
	renderImageToCenterOfRect(renderer, TETRIS_200x66_FILE, rect);

	rect.y += rect.h;
	rect.h = SCREEN_HEIGHT / 9;
	renderTextToCenterOfRect(renderer, "Score: " + std::to_string(score), NORMAL_FONT_LINK, CYAN_COLOR, 28, rect);

	rect.y += rect.h;
	rect.h = SCREEN_HEIGHT / 9;
	renderTextToCenterOfRect(renderer, "Level: " + std::to_string(level), NORMAL_FONT_LINK, LIME_COLOR, 28, rect);

	rect.y += rect.h;
	rect.h = SCREEN_HEIGHT / 9;
	renderTextToCenterOfRect(renderer, "Full lines: " + std::to_string(removedLines), NORMAL_FONT_LINK, BLUE_COLOR, 28, rect);

	rect.y += rect.h + SCREEN_HEIGHT / 24;
	rect.h = SCREEN_HEIGHT / 12;
	renderTextToCenterOfRect(renderer, "NEXT", NORMAL_FONT_LINK, RED_COLOR, 24, rect);

	rect.y += rect.h;
	rect.h = SCREEN_HEIGHT / 12;
	renderTileToCenterOfRect(renderer, nextTile, rect);
}

void renderRightMenu(SDL_Renderer* renderer)
{
    SDL_Rect rect, rect1;
    rect.x = BOARD_STARTX + BOARD_WIDTH_PIXELS;
    rect.w = SCREEN_WIDTH - rect.x;

    rect.y = SCREEN_HEIGHT / 5;
    rect.h = SCREEN_HEIGHT / 9;
    //renderTextToCenterOfRect(renderer, "HELP", NORMAL_FONT_LINK, YELLOW_COLOR, 30, rect);
    renderTextToCenterOfRect(renderer, "HELP", NORMAL_FONT_LINK, WHITE_COLOR, 28, rect);

    rect.x += 40;

    rect.y += rect.h;
    rect.h = SCREEN_HEIGHT / 15;
    renderTextToLeftOfRect(renderer, "   : Rotate", NORMAL_FONT_LINK, WHITE_COLOR, 18, rect);
    rect1 = rect;
    rect1.x += 5;
    renderTextToLeftOfRect(renderer, "↑", NORMAL_FONT_LINK, WHITE_COLOR, 32, rect1);

    rect.y += rect.h;
    rect.h = SCREEN_HEIGHT / 15;
    renderTextToLeftOfRect(renderer, "   : Move left", NORMAL_FONT_LINK, WHITE_COLOR, 18, rect);
    rect1 = rect;
    rect1.x += 5;
    renderTextToLeftOfRect(renderer, "←", NORMAL_FONT_LINK, WHITE_COLOR, 32, rect1);

    rect.y += rect.h;
    rect.h = SCREEN_HEIGHT / 15;
    renderTextToLeftOfRect(renderer, "   : Move right", NORMAL_FONT_LINK, WHITE_COLOR, 18, rect);
    rect1 = rect;
    rect1.x += 5;
    renderTextToLeftOfRect(renderer, "→", NORMAL_FONT_LINK, WHITE_COLOR, 32, rect1);

    rect.y += rect.h;
    rect.h = SCREEN_HEIGHT / 15;
    renderTextToLeftOfRect(renderer, "   : Move down", NORMAL_FONT_LINK, WHITE_COLOR, 18, rect);
    rect1 = rect;
    rect1.x += 5;
    renderTextToLeftOfRect(renderer, "↓", NORMAL_FONT_LINK, WHITE_COLOR, 32, rect1);

    rect.y += rect.h;
    rect.h = SCREEN_HEIGHT / 15;
    renderTextToLeftOfRect(renderer, "[Space]: Hard drop", NORMAL_FONT_LINK, WHITE_COLOR, 18, rect);

    rect.y += rect.h;
    rect.h = SCREEN_HEIGHT / 15;
    renderTextToLeftOfRect(renderer, "[P]: Pause", NORMAL_FONT_LINK, WHITE_COLOR, 18, rect);

    rect.y += rect.h;
    rect.h = SCREEN_HEIGHT / 15;
    renderTextToLeftOfRect(renderer, "[Esc]: Quit", NORMAL_FONT_LINK, WHITE_COLOR, 18, rect);


}

void renderStartMessage(SDL_Renderer* renderer)
{
	SDL_Rect rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT * 3 / 4;
	renderImageToCenterOfRect(renderer, TETRIS_600x200_FILE, rect);

	rect.y += rect.h;
	rect.h = SCREEN_HEIGHT - rect.y;
	renderTextToCenterOfRect(renderer, "Press any key to start", NORMAL_FONT_LINK, LIME_COLOR, 24, rect);
}

void renderQuitMessage(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	rect.x = SCREEN_WIDTH / 2 - BOARD_WIDTH_PIXELS / 2 + 1;
	rect.w = BOARD_WIDTH_PIXELS - 2;

	rect.y = SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 16;
	rect.h = SCREEN_HEIGHT / 8;
	setRenderColor(renderer, BLUE_COLOR);
	SDL_RenderFillRect(renderer, &rect);

	rect.y = SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 16;
	rect.h = SCREEN_HEIGHT / 24;
	renderTextToCenterOfRect(renderer, "Do you really", NORMAL_FONT_LINK, RED_COLOR, 20, rect);

	rect.y += rect.h;
	rect.h = SCREEN_HEIGHT / 24;
	renderTextToCenterOfRect(renderer, "want to quit?", NORMAL_FONT_LINK, RED_COLOR, 20, rect);

	rect.y += rect.h;
	rect.h = SCREEN_HEIGHT / 24;
	renderTextToCenterOfRect(renderer, "[Y]: Yes  [N]: No", NORMAL_FONT_LINK, ORANGE_COLOR, 16, rect);

}
