enum marker {M_B, M_X, M_O};

class tictactoe
{
    public:
        tictactoe();

        int get_player();
        void set_player(int x);
        bool winner();
        void print_board();
        void get_move(int& row, int& column);
        void random_ai_move(int& row, int& column);
        void update_board(int row, int column);

    private:
        marker board[3][3];
        int player;

        bool valid(int row, int column);
        bool row_check();
        bool col_check();
        bool diag_check();
};
