#pragma once
#define imageIdx 7
class Tile
{
public:
    int         F, G, H;//Ÿ�� ���
    Int2        idx;    //Ÿ�� �ε���
    Tile*       P;      //���� ���Ž�Ų Ÿ��
    bool        isFind; //�˻������� �ִ°�?
    int         state;
    Vector2     Pos;

    void ClearCost();         //��� �ʱ�ȭ
    void ClacH(Int2 DestIdx); //H����ض�
    void ClacF(); //F����ض�
};
//               Ÿ���ּ�,�񱳰�
using PTile = pair<Tile*, int>;

struct compare
{
    //������ �����ε�
    bool operator()(PTile& a, PTile& b)
    {
        return a.second > b.second;
    }
};

enum TileState
{
    TILE_NONE,
    TILE_WALL,
    TILE_PLATFORM
};

class ObTileMap : public GameObject
{
private:
    VertexTile*             vertices;
    ID3D11Buffer *          vertexBuffer;
    vector<vector<Tile>>    Tiles;
public:
    Int2                    tileSize;   //10x10 , 4x4
    ObImage *               tileImages[imageIdx];
    string                  file;

public:
    ObTileMap();
    ~ObTileMap();


    void        Render()override;
    void        SetTile(Int2 TileIdx, Int2 FrameIdx, int ImgIdx = 0 ,
        byte TileState = TILE_NONE , Color color = Color(0.5f, 0.5f, 0.5f, 0.5f));
    void        SetLight(Int2 TileIdx, int light);
    void        UpdateSub();
    int         GetTileState(Int2 TileIdx);
    void        SetTileState(Int2 TileIdx, int TileState);
    Vector2     GetTilePosition(Int2 TileIdx);
    bool        WorldPosToTileIdx(Vector2 WPos, Int2 & TileIdx);
    void        ResizeTile(Int2 TileSize);
    void        Save();
    void        Load();
    Int2        GetTileSize() { return tileSize; };
    void        CreateTileCost();
    bool        PathFinding(Int2 sour, Int2 dest, OUT vector<Tile*>& way);
};

