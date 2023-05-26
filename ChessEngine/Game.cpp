#include "Game.h"

void Game::reset()
{
	castlingRights.clear();
	enPassantPos = Position{ -1,-1 };
	halfMoves = 0;
	fullMoves = 0;

	for (size_t rank = 0; rank < 8; rank++)
	{
		for (size_t file = 0; file < 8; file++)
		{
			board[rank][file] = Piece();
		}
	}
}

void Game::setPiece(const fenparserpp::BoardPos& bpos, fenparserpp::Piece piece, fenparserpp::PieceColor pieceColor)
{
	Position pos = { bpos.getRank(), bpos.getFile() };

	PieceColor pc;
	if (pieceColor == fenparserpp::PieceColor::WHITE)
		pc = PieceColor::WHITE;
	else
		pc = PieceColor::BLACK;

	switch (piece)
	{
	case fenparserpp::Piece::BISHOP:
		putPiece(pos, Piece(PieceKind::BISHOP, pc));
		break;
	case fenparserpp::Piece::KING:
		putPiece(pos, Piece(PieceKind::KING, pc));
		break;
	case fenparserpp::Piece::KNIGHT:
		putPiece(pos, Piece(PieceKind::KNIGHT, pc));
		break;
	case fenparserpp::Piece::PAWN:
		putPiece(pos, Piece(PieceKind::PAWN, pc));
		break;
	case fenparserpp::Piece::QUEEN:
		putPiece(pos, Piece(PieceKind::QUEEN, pc));
		break;
	case fenparserpp::Piece::ROOK:
		putPiece(pos, Piece(PieceKind::ROOK, pc));
		break;
	default:
		putPiece(pos, Piece(PieceKind::NONE, pc));
		break;
	}

}

void Game::setCastleRight(fenparserpp::CastleRight right)
{
	CastleRight cr;

	switch (right)
	{
	case fenparserpp::CastleRight::BLACK_KINGSIDE_CASTLE:
		cr = CastleRight::BLACK_KINGSIDE_CASTLE;
		break;
	case fenparserpp::CastleRight::BLACK_QUEENSIDE_CASTLE:
		cr = CastleRight::BLACK_QUEENSIDE_CASTLE;
		break;
	case fenparserpp::CastleRight::WHITE_KINGSIDE_CASTLE:
		cr = CastleRight::WHITE_KINGSIDE_CASTLE;
		break;
	case fenparserpp::CastleRight::WHITE_QUEENSIDE_CASTLE:
		cr = CastleRight::WHITE_QUEENSIDE_CASTLE;
		break;
	}

	castlingRights.insert(cr);
}

void Game::setEnPassantPos(const fenparserpp::BoardPos& bpos)
{
	enPassantPos = Position{ bpos.getRank(), bpos.getFile() };
}

void Game::setHalfMoves(int hmoves)
{
	halfMoves = hmoves;
}

void Game::setFullMoves(int fmoves)
{
	fullMoves = fmoves;
}

void Game::setToPlay(fenparserpp::PieceColor color)
{
	if (color == fenparserpp::PieceColor::BLACK)
		toPlay = PieceColor::BLACK;
	else
		toPlay = PieceColor::WHITE;
}

Game::Game()
{
	reset();
}

void Game::putPiece(Position pos, Piece pc)
{
	board[pos.rank][pos.file] = pc;
}

void Game::printBoardGUI(std::vector<Position> bestMove) const
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Chess Board");

	// Load the images for chess pieces
	sf::Texture texture;

	// Load the piece images
	sf::Texture pieceTextures[12];
	std::string pieceNames[12] = { "WhiteRook", "WhiteKnight", "WhiteBishop", "WhiteQueen", "WhiteKing", "WhitePawn", "BlackRook", "BlackKnight", "BlackBishop", "BlackQueen", "BlackKing", "BlackPawn" };

	for (int i = 0; i < 12; i++) {
		std::string fileName = "Images\\" + pieceNames[i] + ".png";
		if (!pieceTextures[i].loadFromFile(fileName)) {
			std::cout << "Failed to load piece image: " << fileName << std::endl;
			return;
		}
	}

	// Set up the chessboard squares
	const int squareSize = 100;
	sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
	square.setFillColor(sf::Color::White);
	sf::RectangleShape highlight(sf::Vector2f(squareSize, squareSize));
	highlight.setFillColor(sf::Color(26, 214, 51, 128)); // Semi-transparent green
	sf::RectangleShape blueSquare(sf::Vector2f(squareSize, squareSize));
	blueSquare.setFillColor(sf::Color(45, 139, 168, 90));

	// Create sprites for the chess pieces
	sf::Sprite chessPieces[12];

	for (int i = 0; i < 12; i++) {
		sf::Vector2u imageSize = pieceTextures[i].getSize();
		float scale = static_cast<float>(squareSize - 2) / std::max(imageSize.x, imageSize.y);
		chessPieces[i].setTexture(pieceTextures[i]);
		chessPieces[i].setScale(scale, scale);
	}
	bool imageDisplayed = false;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (!imageDisplayed) {
			window.clear();

			for (int col = 0; col < 8; col++)
			{
				for (int row = 7; row >= 0; row--) {
					if ((col % 2 == 0 && row % 2 == 0) || (col % 2 == 1 && row % 2 == 1)) {
						square.setPosition(col * squareSize, row * squareSize);
						window.draw(square);
					}
					else {
						highlight.setPosition(col * squareSize, row * squareSize);
						window.draw(highlight);
					}


					// Draw the piece if present

					Piece piece = board[7 - row][col];
					int index;
					switch (piece.getKind())
					{
					case PieceKind::ROOK:
						if (piece.getColor() == PieceColor::WHITE) {
							index = 0;
						}
						else {
							index = 6;
						}
						break;

					case PieceKind::KNIGHT:
						if (piece.getColor() == PieceColor::WHITE) {
							index = 1;
						}
						else {
							index = 7;
						}
						break;

					case PieceKind::BISHOP:
						if (piece.getColor() == PieceColor::WHITE) {
							index = 2;
						}
						else {
							index = 8;
						}
						break;

					case PieceKind::QUEEN:
						if (piece.getColor() == PieceColor::WHITE) {
							index = 3;
						}
						else {
							index = 9;
						}
						break;

					case PieceKind::KING:
						if (piece.getColor() == PieceColor::WHITE) {
							index = 4;
						}
						else {
							index = 10;
						}
						break;

					case PieceKind::PAWN:
						if (piece.getColor() == PieceColor::WHITE) {
							index = 5;
						}
						else {
							index = 11;
						}
						break;

					default:
						index = -1;
						continue;
					}

					chessPieces[index].setPosition(col * squareSize, row * squareSize);
					window.draw(chessPieces[index]);

				}
			}
			if (bestMove[0].rank != -1) {
				highlight.setPosition(bestMove[0].file * squareSize, (7 - bestMove[0].rank) * squareSize);
				highlight.setFillColor(sf::Color(26, 214, 51));
				window.draw(highlight);
				blueSquare.setPosition(bestMove[0].file * squareSize, (7 - bestMove[0].rank) * squareSize);
				window.draw(blueSquare);

				Piece piece = board[bestMove[0].rank][bestMove[0].file];
				int index;
				switch (piece.getKind())
				{
				case PieceKind::ROOK:
					if (piece.getColor() == PieceColor::WHITE) {
						index = 0;
					}
					else {
						index = 6;
					}
					break;

				case PieceKind::KNIGHT:
					if (piece.getColor() == PieceColor::WHITE) {
						index = 1;
					}
					else {
						index = 7;
					}
					break;

				case PieceKind::BISHOP:
					if (piece.getColor() == PieceColor::WHITE) {
						index = 2;
					}
					else {
						index = 8;
					}
					break;

				case PieceKind::QUEEN:
					if (piece.getColor() == PieceColor::WHITE) {
						index = 3;
					}
					else {
						index = 9;
					}
					break;

				case PieceKind::KING:
					if (piece.getColor() == PieceColor::WHITE) {
						index = 4;
					}
					else {
						index = 10;
					}
					break;

				case PieceKind::PAWN:
					if (piece.getColor() == PieceColor::WHITE) {
						index = 5;
					}
					else {
						index = 11;
					}
					break;

				default:
					index = -1;
					break;
				}
				if ((bestMove[1].file % 2 == 0 && (7 - bestMove[1].rank) % 2 == 0) || (bestMove[1].file % 2 == 1 && (7-bestMove[1].rank) % 2 == 1)) {
					square.setPosition(bestMove[1].file * squareSize, (7 - bestMove[1].rank) * squareSize);
					window.draw(square);
				}
				else {
					highlight.setPosition(bestMove[1].file * squareSize, (7 - bestMove[1].rank) * squareSize);
					window.draw(highlight);
				}
				blueSquare.setPosition(bestMove[1].file * squareSize, (7 - bestMove[1].rank) * squareSize);
				window.draw(blueSquare);				
				chessPieces[index].setPosition(bestMove[1].file * squareSize, (7 - bestMove[1].rank) * squareSize);
				window.draw(chessPieces[index]);


			}

			window.display();

			imageDisplayed = true;
		}

	}
}

void Game::printBoard() const
{
	for (int i = 7; i > -1; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << board[i][j] << " ";
		}
		std::cout << "\n";
	}
}

bool Game::isInsideBoard(Position pos) const
{
	return (pos.rank >= 0 && pos.rank < 8 && pos.file >= 0 && pos.file < 8);
}

bool Game::containsPiece(Position pos) const
{
	Piece pc = board[pos.rank][pos.file];
	return pc.getKind() != PieceKind::NONE;
}

bool Game::containsPiece(Position pos, const Piece& pc) const
{
	Piece piece = board[pos.rank][pos.file];
	return piece.getKind() == pc.getKind() && piece.getColor() == pc.getColor();
}

bool Game::containsEnemyPiece(Position pos, PieceColor color) const
{
	Piece pc = board[pos.rank][pos.file];
	return pc.getKind() != PieceKind::NONE && pc.getColor() != color;
}

bool Game::containsOwnPiece(Position pos, PieceColor color) const
{
	Piece pc = board[pos.rank][pos.file];
	return pc.getKind() != PieceKind::NONE && pc.getColor() == color;
}

Position Game::getKing(PieceColor color) const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece pc = board[i][j];
			if (pc.getKind() == PieceKind::KING && pc.getColor() == color)
				return Position{ i,j };
		}
	}

	return Position{ -1,-1 };
}

std::vector<Position> Game::getValidSquares(Position pos) const
{
	std::vector<Position> squares;

	Piece pc = board[pos.rank][pos.file];

	std::vector<std::vector<int>> moves;
	std::vector<std::vector<int>> attacks;

	switch (pc.getKind())
	{
	case PieceKind::ROOK:
		moves = { {1,0},{0,1},{-1,0},{0,-1} };
		
		for (auto move : moves)
		{
			Position nextPos = { pos.rank + move[0], pos.file + move[1] };
			while (isInsideBoard(nextPos))
			{
				if (containsOwnPiece(nextPos, pc.getColor())) break;
				squares.push_back(nextPos);
				if (containsEnemyPiece(nextPos, pc.getColor())) break;
				nextPos = { nextPos.rank + move[0], nextPos.file + move[1] };
			}
		}
		break;
	case PieceKind::BISHOP:
		moves = { {1,1},{-1,1},{-1,-1},{1,-1} };

		for (auto move : moves)
		{
			Position nextPos = { pos.rank + move[0], pos.file + move[1] };
			while (isInsideBoard(nextPos))
			{
				if (containsOwnPiece(nextPos, pc.getColor())) break;
				squares.push_back(nextPos);
				if (containsEnemyPiece(nextPos, pc.getColor())) break;
				nextPos = { nextPos.rank + move[0], nextPos.file + move[1] };
			}
		}
		break;
	case PieceKind::QUEEN:
		moves = { {1,1},{-1,1},{-1,-1},{1,-1},{1,0},{0,1},{-1,0},{0,-1} };

		for (auto move : moves)
		{
			Position nextPos = { pos.rank + move[0], pos.file + move[1] };
			while (isInsideBoard(nextPos))
			{
				if (containsOwnPiece(nextPos, pc.getColor())) break;
				squares.push_back(nextPos);
				if (containsEnemyPiece(nextPos, pc.getColor())) break;
				nextPos = { nextPos.rank + move[0], nextPos.file + move[1] };
			}
		}
		break;
	case PieceKind::KNIGHT:
		moves = { {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2} };

		for (auto move : moves)
		{
			Position nextPos = { pos.rank + move[0], pos.file + move[1] };
			if (isInsideBoard(nextPos))
			{
				if (containsOwnPiece(nextPos, pc.getColor())) continue;
				squares.push_back(nextPos);
			}
		}
		break;
	case PieceKind::KING:
		moves = { {1,1},{-1,1},{-1,-1},{1,-1},{1,0},{0,1},{-1,0},{0,-1} };

		for (auto move : moves)
		{
			Position nextPos = { pos.rank + move[0], pos.file + move[1] };
			if (isInsideBoard(nextPos))
			{
				if (containsOwnPiece(nextPos, pc.getColor())) continue;
				squares.push_back(nextPos);
			}
		}
		break;
	case PieceKind::PAWN:
	{
		moves = { { 1,0 } };
		attacks = { {1,1}, {1,-1} };
		if (pc.getColor() == PieceColor::BLACK)
		{
			moves[0][0] *= -1;
			attacks[0][0] *= -1;
			attacks[1][0] *= -1;
		}

		Position nextPos = { pos.rank + moves[0][0], pos.file + moves[0][1] };
		if (isInsideBoard(nextPos) && !containsPiece(nextPos))
		{
			squares.push_back(nextPos);
			nextPos = { nextPos.rank + moves[0][0], nextPos.file + moves[0][1] };
			if (isInsideBoard(nextPos) && !containsPiece(nextPos) &&
				((pc.getColor() == PieceColor::WHITE && pos.rank == 1) || (pc.getColor() == PieceColor::BLACK && pos.rank == 6)))
			{
				squares.push_back(nextPos);
			}
		}

		for (auto attack : attacks)
		{
			nextPos = { pos.rank + attack[0], pos.file + attack[1] };
			if (isInsideBoard(nextPos) && containsEnemyPiece(nextPos, pc.getColor()))
			{
				squares.push_back(nextPos);
			}
		}
		break;
	}
	default:
		break;
	}

	return squares;
}

bool Game::isCheck(PieceColor color) const
{
	Position kingPosition = getKing(color);
	PieceColor opposingColor = color == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE;

	// Check for diagonal threats
	if (checkDiagonalThreat(kingPosition, color)) return true;

	// Check for orthogonal threats
	if (checkOrthogonalThreat(kingPosition, color)) return true;

	// Check for knight threats
	if (checkKnightThreat(kingPosition, color)) return true;

	// Check for pawn threats
	if (checkPawnThreat(kingPosition, color)) return true;

	// Check for enemy king threats
	if (checkKingThreat(kingPosition, color)) return true;

	return false;
}

bool Game::checkDiagonalThreat(Position pos, PieceColor color) const
{
	std::vector<std::vector<int>> patterns = { {1,1},{-1,1},{-1,-1},{1,-1} };
	Piece enemyBishop(PieceKind::BISHOP, getOpposingColor(color));
	Piece enemyQueen(PieceKind::QUEEN, getOpposingColor(color));

	for (auto pattern : patterns)
	{
		Position nextPos = { pos.rank + pattern[0], pos.file + pattern[1] };
		while (isInsideBoard(nextPos))
		{
			if (containsOwnPiece(nextPos, color)) break;
			if (containsPiece(nextPos, enemyBishop) || containsPiece(nextPos, enemyQueen)) return true;
			nextPos = { nextPos.rank + pattern[0], nextPos.file + pattern[1] };
		}
	}

	return false;
}

bool Game::checkOrthogonalThreat(Position pos, PieceColor color) const
{
	std::vector<std::vector<int>> patterns = { {1,0},{0,1},{-1,0},{0,-1} };
	Piece enemyRook(PieceKind::ROOK, getOpposingColor(color));
	Piece enemyQueen(PieceKind::QUEEN, getOpposingColor(color));

	for (auto pattern : patterns)
	{
		Position nextPos = { pos.rank + pattern[0], pos.file + pattern[1] };
		while (isInsideBoard(nextPos))
		{
			if (containsOwnPiece(nextPos, color)) break;
			if (containsPiece(nextPos, enemyRook) || containsPiece(nextPos, enemyQueen)) return true;
			nextPos = { nextPos.rank + pattern[0], nextPos.file + pattern[1] };
		}
	}

	return false;
}

bool Game::checkKnightThreat(Position pos, PieceColor color) const
{
	std::vector<std::vector<int>> patterns = { {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2} };
	Piece enemyKnight(PieceKind::KNIGHT, getOpposingColor(color));

	for (auto pattern : patterns)
	{
		Position nextPos = { pos.rank + pattern[0], pos.file + pattern[1] };
		if (isInsideBoard(nextPos))
		{
			if (containsPiece(nextPos, enemyKnight)) return true;
		}
	}

	return false;
}

bool Game::checkPawnThreat(Position pos, PieceColor color) const
{
	Piece pc;
	PieceColor opposingColor = getOpposingColor(color);
	if (color == PieceColor::WHITE)
	{
		pc = board[pos.rank + 1][pos.file + 1];
		if (pc.getKind() == PieceKind::PAWN && pc.getColor() == opposingColor) return true;
		pc = board[pos.rank + 1][pos.file - 1];
		if (pc.getKind() == PieceKind::PAWN && pc.getColor() == opposingColor) return true;
	}
	else
	{
		pc = board[pos.rank - 1][pos.file + 1];
		if (pc.getKind() == PieceKind::PAWN && pc.getColor() == opposingColor) return true;
		pc = board[pos.rank - 1][pos.file - 1];
		if (pc.getKind() == PieceKind::PAWN && pc.getColor() == opposingColor) return true;
	}

	return false;
}

bool Game::checkKingThreat(Position pos, PieceColor color) const
{
	std::vector<std::vector<int>> patterns = { {1,0},{0,1},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1} };
	Piece enemyKing(PieceKind::KING, getOpposingColor(color));

	for (auto pattern : patterns)
	{
		Position nextPos = { pos.rank + pattern[0], pos.file + pattern[1] };
		if (isInsideBoard(nextPos) && containsPiece(nextPos, enemyKing))
		{
			return true;
		}
	}

	return false;
}

PieceColor Game::getOpposingColor(PieceColor color) const
{
	return color == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE;
}

bool Game::isValidMove(Position source, Position target)
{
	Piece sourcePiece = board[source.rank][source.file];
	Piece targetPiece = board[target.rank][target.file];

	putPiece(target, sourcePiece);
	putPiece(source, Piece());

	// Check if king is in check
	bool isInCheck = isCheck(toPlay);

	// Return to original position
	putPiece(source, sourcePiece);
	putPiece(target, targetPiece);

	return !isInCheck;
}

double Game::evaluate() const
{
	double whiteEval = evaluateColor(PieceColor::WHITE);
	double blackEval = evaluateColor(PieceColor::BLACK);
	return whiteEval - blackEval;
}

double Game::evaluateColor(PieceColor color) const
{
	double eval = 0.0;

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			Piece piece = board[i][j];
			if (piece.getColor() != color) continue;

			switch (piece.getKind())
			{
			case PieceKind::PAWN:
				eval += 1.0;
				break;
			case PieceKind::KNIGHT:
			case PieceKind::BISHOP:
				eval += 3.0;
				break;
			case PieceKind::ROOK:
				eval += 5.0;
				break;
			case PieceKind::QUEEN:
				eval += 9.0;
				break;
			default:
				break;
			}
		}
	}

	return eval;
}

std::vector<Position> Game::getPiecePositions(PieceColor color) const
{
	std::vector<Position> piecePositions;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece piece = board[i][j];
			if (piece.getKind() != PieceKind::NONE && piece.getColor() == color)
				piecePositions.push_back(Position{ i,j });
		}
	}

	return piecePositions;
}

std::vector<std::vector<Position>> Game::getValidMoves(Position pos)
{
	std::vector<Position> validSquares = getValidSquares(pos);
	std::vector<std::vector<Position>> validMoves;
	for (auto validSquare : validSquares)
	{
		if (isValidMove(pos, validSquare))
		{
			std::vector<Position> move = { pos, validSquare };
			validMoves.push_back(move);
		}
	}

	return validMoves;
}

std::vector<std::vector<Position>> Game::getPlayerValidMoves(PieceColor color)
{
	std::vector<Position> piecePositions = getPiecePositions(color);
	std::vector<std::vector<Position>> moves;
	for (auto pos : piecePositions)
	{
		std::vector<std::vector<Position>> validMoves = getValidMoves(pos);
		moves.insert(moves.end(), validMoves.begin(), validMoves.end());
	}

	return moves;
}

void Game::makeMove(Position source, Position target)
{
	Piece piece = board[source.rank][source.file];

	// check for pawn promotion
	if (piece.getKind() == PieceKind::PAWN)
	{
		if (piece.getColor() == PieceColor::WHITE && source.rank == 6)
		{
			piece = Piece(PieceKind::QUEEN, PieceColor::WHITE);
		}
		else if (piece.getColor() == PieceColor::BLACK && source.rank == 1)
		{
			piece = Piece(PieceKind::QUEEN, PieceColor::BLACK);
		}
	}

	board[target.rank][target.file] = piece;
	board[source.rank][source.file] = Piece();
}

void Game::setTurn(PieceColor color)
{
	toPlay = color;
}

PieceColor Game::getTurn() const
{
	return toPlay;
}
