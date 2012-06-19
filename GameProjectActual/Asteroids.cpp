#include "Asteroid.h"
#include "AsteroidOre.h"
#include "Ore.h"
#include "Asteroids.h"
#include "Animation.h"
#include "AnimationManager.h"
#include "Explosion.h"
#include "GameUtil.h"
#include "GameWindow.h"
#include "GameWorld.h"
#include "GameDisplay.h"
#include "GUILabel.h"
#include "GUISelectionBox.h"
#include "Image.h"
#include "ImageManager.h"
#include "Shape.h"
#include "Spaceship.h"
#include "Sprite.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Drone.h"
#include "Order.h"
#include <cmath>

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

bool Asteroids::mConsoleDebug = true;

/** Constructor. Takes arguments from command line, just in case. */
Asteroids::Asteroids(int argc, char *argv[])
    : GameSession(argc, argv)
{
}

/** Destructor. */
Asteroids::~Asteroids(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Start an asteroids game. */
void Asteroids::Start()
{
    // Add a player (watcher) to the game world
    mGameWorld->AddListener(&mPlayer);
    // Add a score keeper to the game world
    mGameWorld->AddListener(&mScoreKeeper);
    // Add this class as a listener of the score keeper
    mScoreKeeper.AddListener(this);
    // Add this class as a listener of the game world
    mGameWorld->AddListener(this);
    // Add this class as a listener of the player
    mPlayer.AddListener(this);
    // Create user interface
    CreateGUI();

    // Create an ambient light to show sprite textures
    GLfloat ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light);
    glEnable(GL_LIGHT1);

    mSelectedShape = new Shape("ASSETS/selected.shape");

    Animation *explosion_anim = AnimationManager::GetInstance().CreateAnimationFromRawRGBA("explosion", 64, 1024, 64, 64, "ASSETS/explosion_fs.raw", "ASSETS/explosion_fs_alpha.raw");
    Animation *asteroid1_anim = AnimationManager::GetInstance().CreateAnimationFromRawRGBA("asteroid1", 128, 8192, 128, 128, "ASSETS/asteroid1_fs.raw", "ASSETS/asteroid1_fs_alpha.raw");
    Animation *asteroidOre1_anim = AnimationManager::GetInstance().CreateAnimationFromRawRGBA("asteroidOre1", 128, 8192, 128, 128, "ASSETS/asteroidOre1_fs.raw", "ASSETS/asteroidOre1_fs_alpha.raw");
    //Animation *droid_anim = AnimationManager::GetInstance().CreateAnimationFromRawRGBA("droid1", );
    Animation *spaceship_anim = AnimationManager::GetInstance().CreateAnimationFromRawRGBA("spaceship", 128, 128, 128, 128, "ASSETS/spaceship_fs.raw", "ASSETS/spaceship_fs_alpha.raw");

    // Add this as a listener to the world and the keyboard
    mGameWindow->AddKeyboardListener(this);
    // Add this as a listener to the world and the mouse
    mGameWindow->AddMouseListener(this);
    // Add the selection box to the world
    mGameWorld->GiveSelectionBox(mSelectionBox);


    // Create a spaceship and add it to the world
    //mGameWorld->AddObject(CreateSpaceship());
    // Create some asteroids and add them to the world
    mLevel = 1;
    mAsteroidCount = 1;

    int w = mGameDisplay->GetWidth();
    int h = mGameDisplay->GetHeight();

    cout << "width : " << w;
    cout << "height : " << h;

    // creating asteroids
    for (int i = 0; i < 10; i++)
    {
        int x = (rand() % w) - w/2;
        int y = (rand() % h) - h/2;
        mGameWorld->AddObject(CreateAsteroid(x,y));
        mAsteroidCount++;
    }

    //creating ore asteroids
    for (int i = 0; i < 10; i++)
    {
        int x = (rand() % w) - w/2;
        int y = (rand() % h) - h/2;
        mGameWorld->AddObject(CreateAsteroidOre(x,y));
        mAsteroidCount++;
    }


    // creating drones
    float rAngle = 0;
    GLVector3f zero(0.0, 0.0, 0.0);

    for(int i = 0; i < 2; i++){
        GLVector3f new_drone_offset(cos(DEG2RAD*rAngle), sin(DEG2RAD*rAngle), 0.0);
        new_drone_offset.normalize();
        GLVector3f drone_position = zero + (new_drone_offset * 20);

        mGameWorld->AddObject(CreateDrone(drone_position.x,drone_position.y));
        rAngle += 360 / 2;
    }

    // creaing a single ore for testing
    mGameWorld->AddObject(CreateOre(100,0));

    // Start the game
    GameSession::Start();
}

/** Stop the current game. */
void Asteroids::Stop()
{
    // Stop the game
    GameSession::Stop();
}


// PUBLIC INSTANCE METHODS IMPLEMENTING IMouseListener ////////////////////////

void Asteroids::OnMouseDragged(int x, int y)
{
    GLVector2i mouseVector(GLVector2i(x, mGameDisplay->GetHeight() - y));
//        mSpaceship->Shoot();


//        mGameWorld->AddObject(CreateAsteroid(x,y));
//        mGameWorld->AddObject(CreateAsteroid());
//        mAsteroidCount++;
    const int zl = mGameWindow->GetZoomLevel();
    GLVector3f m2w((x - mGameDisplay->GetWidth()/2)/zl + mCameraFocus->x, (mGameDisplay->GetHeight()/2 - y)/zl + mCameraFocus->y, 0.0);

    mSelectionBox->SetMouse(GLVector2i(x,y));
    mSelectionBox->SetWorldCoord1(m2w);

//    if(mMoveCamera) {
//        GLVector2i m = GLVector2i(x - mGameWorld->GetWidth(), (y - mGameWorld->GetHeight()) * -1);
//        float delta = sqrt(pow((m.x - mCameraFocus.x),2) * pow((m.y - mCameraFocus.y),2));
//        delta = delta/10.0;
////        mCameraFocus;
//        cout << "Delta       : " << delta << endl;
//        cout << "Mouse Vector: " << m << endl;
//        mCameraFocus += m*delta;
//    }
//    cout << "Camera Focus: " << mCameraFocus << endl;
//    cout << endl;
}

void Asteroids::OnMouseButton(int button, int state, int x, int y)
{

    if(state == GLUT_DOWN)
    {
        if(button == GLUT_RIGHT_BUTTON)
        {
            mMoveCamera = true;

            // Calculate world coordinates
            const int zl = mGameWindow->GetZoomLevel();
            GLVector3f m2w((x - mGameDisplay->GetWidth()/2)/zl + mCameraFocus->x, (mGameDisplay->GetHeight()/2 - y)/zl + mCameraFocus->y, 0.0);

            SmartPtr<GameObject> checkSelect = mGameWorld->GetOnClickSelect(m2w);
            SmartPtr<Order> o = NULL;
            if(checkSelect.GetPtr() == NULL) {
                o = new Order(ORDER_MOVE);
                o->SetDestination(m2w);
            } else {
                o = new Order(ORDER_ATTACK);
                o->SetTarget(checkSelect);
            }
            mGameWorld->AssignOrderToSelected(o);
        }
        if(button == GLUT_LEFT_BUTTON)
        {
//            cout << endl;
//            cout << "GLUT MOUSE: " << x << "\t" << y << endl;

//            GLVector2i mouseVector(GLVector2i(x, mGameDisplay->GetHeight() - y));
//            cout << "GUI COORDS: " << mouseVector.x << "\t" << mouseVector.y << endl;

//            float dw = mGameDisplay->GetWidth();
//            float dh = mGameDisplay->GetHeight();
//            cout << "DISPLAY WH: " << dw << "\t" << dh << endl;

            // Get game zoom level
//            cout << "ZOOM LEVEL: " << zl << endl;

//            GLVector3f mouse2world((x - dw/2)/zl + mCameraFocus->x, (dh/2 - y)/zl + mCameraFocus->y, 0.0);
//
//            cout << "M2W COORDS: " << mouse2world.x << "\t" << mouse2world.y << endl;
//            cout << "CAM  FOCUS: " << mCameraFocus->x << "\t" << mCameraFocus->y << endl;

//            mGameWorld->AddObject(CreateAsteroid(x,y));
//            mGameWorld->AddObject(CreateAsteroid());
//            mAsteroidCount++;

            // get zoom level of the game to calculate world coordinates
            const int zl = mGameWindow->GetZoomLevel();
            // Calculate the world coordinate corresponding to mouse coordinates (m2w = mouse to world).
            GLVector3f m2w((x - mGameDisplay->GetWidth()/2)/zl + mCameraFocus->x, (mGameDisplay->GetHeight()/2 - y)/zl + mCameraFocus->y, 0.0);


            // Make the selection box visible
            mSelectionBox->SetVisible(true);
            // Set the starting point for the box to be the mouse coordinates
            mSelectionBox->SetStart(GLVector2i(x,y));
            // Set the second point of the box (where mouse is) to also be the mouse coordinates to reset it
            mSelectionBox->SetMouse(GLVector2i(x,y));
            // Set the world coordinates coresponding to  the mouse coordinates
            mSelectionBox->SetWorldCoord1(m2w);
            mSelectionBox->SetWorldCoord2(m2w);

            SmartPtr<GameObject> selectedGO = mGameWorld->GetOnClickSelect(m2w);
            if(selectedGO.GetPtr() != NULL){
                if(selectedGO->GetType() == GameObjectType("Drone"))
                {
                    selectedGO->MakeSelected();
                }
            }
            cout << "CLICK FOUND: " << selectedGO.GetPtr() << endl;

            //mGameWorld->AddObject(CreateAsteroid(mouse2world.x, mouse2world.y));
//            SmartPtr<GameObject> a = CreateAsteroid(mGameWorld->GetHeight(), mGameWorld->GetWidth());
            //a->SetVelocity(GLVector3f(0.0,-100.0,0.0));
            //mGameWorld->AddObject(a);
            //mAsteroidCount++;
        }
    }
    else if (state == GLUT_UP)
    {
        mSelectionBox->SetVisible(false);
        mMoveCamera = false;
    }
}

void Asteroids::OnMouseMoved(int x, int y)
{
    glutGet(GLUT_ELAPSED_TIME);

//    int width = mGameDisplay->GetHeight();
//    int height = mGameDisplay->GetWidth();
//
//    GLVector2i m = GLVector2i(x - width, (y - height) * -1);
//    int mb(20); //movement border
//
//    cout << "M: " << m << endl;
//
//    if(m.x < (mCameraFocus->x - width  )) mCameraFocus->x -= 2;
//    if(m.x > ( width  )) mCameraFocus->x += 2;
//    if(m.y < (-height )) mCameraFocus->y -= 2;
//    if(m.y > ( height )) mCameraFocus->y += 2;
//
//    mCameraFocus->x += m.x;
//    mCameraFocus->y += m.y;
//
//    cout << "w/h " << width << "/" << height << ":" << mb << endl;
//    cout << "Camera Focus: " << (*mCameraFocus) << endl;

//    cout << "[" << x << " , " << y << " ]" << endl;
}


// PUBLIC INSTANCE METHODS IMPLEMENTING IKeyboardListener /////////////////////

void Asteroids::OnKeyPressed(uchar key, int x, int y)
{
    switch (key)
    {
    case ' ':
        mSpaceship->Shoot();
        break;
    case 'w':
    case 'W':
        CameraMoveUp();
        break;
    case 's':
    case 'S':
        CameraMoveDown();
        break;
    case 'a':
    case 'A':
        CameraMoveLeft();
        break;
    case 'd':
    case 'D':
        CameraMoveRight();
        break;
    case 'n':
    case 'N':
        if(mSpaceship.GetPtr() == NULL) mGameWorld->AddObject(CreateSpaceship());
        break;
    default:
        break;
    }
}

void Asteroids::OnKeyReleased(uchar key, int x, int y) {}

void Asteroids::OnSpecialKeyPressed(int key, int x, int y)
{
    if(mSpaceship.GetPtr() != NULL){
        switch (key)
        {
            // If up arrow key is pressed start applying forward thrust
        case GLUT_KEY_UP:
            mSpaceship->Thrust(50);
            break;
            // If up arrow key is released stop applying forward thrust
        case GLUT_KEY_DOWN:
            mSpaceship->Thrust(-50);
            break;
            // If left arrow key is pressed start rotating anti-clockwise
        case GLUT_KEY_LEFT:
            mSpaceship->Rotate(90);
            break;
            // If right arrow key is pressed start rotating clockwise
        case GLUT_KEY_RIGHT:
            mSpaceship->Rotate(-90);
            break;
            // Default case - do nothing
        default:
            break;
        }
    }
}

void Asteroids::OnSpecialKeyReleased(int key, int x, int y)
{
    if(mSpaceship.GetPtr() != NULL){
        switch (key)
        {
            // If up arrow key is released stop applying forward thrust
        case GLUT_KEY_UP:
            mSpaceship->Thrust(0);
            break;
            // If up arrow key is released stop applying forward thrust
        case GLUT_KEY_DOWN:
            mSpaceship->Thrust(0);
            break;
            // If left arrow key is released stop rotating
        case GLUT_KEY_LEFT:
            mSpaceship->Rotate(0);
            break;
            // If right arrow key is released stop rotating
        case GLUT_KEY_RIGHT:
            mSpaceship->Rotate(0);
            break;
            // Default case - do nothing
        default:
            break;
        }
    }
}

// PUBLIC INSTANCE METHODS IMPLEMENTING IScoreListener ////////////////////////

void Asteroids::OnScoreChanged(int score)
{
    // Format the score message using an string-based stream
    std::ostringstream msg_stream;
    msg_stream << "Resources: " << score;
    // Get the score message as a string
    std::string score_msg = msg_stream.str();
    mScoreLabel->SetText(score_msg);
}

// PUBLIC INSTANCE METHODS IMPLEMENTING IPlayerListener ////////////////////////

void Asteroids::OnPlayerKilled(int lives_left)
{
    SmartPtr<GameObject> explosion = CreateExplosion();
    explosion->SetPosition(mSpaceship->GetPosition());
    explosion->SetRotation(mSpaceship->GetRotation());
    mGameWorld->AddObject(explosion);
    // Format the lives left message using an string-based stream`
    std::ostringstream msg_stream;
    msg_stream << "Lives: " << lives_left;
    // Get the lives left message as a string
    std::string lives_msg = msg_stream.str();
    mLivesLabel->SetText(lives_msg);

    if (lives_left > 0)
    {
        SetTimer(1000, CREATE_NEW_PLAYER);
    }
    else
    {
        SetTimer(500, SHOW_GAME_OVER);
    }
}

// PUBLIC INSTANCE METHODS IMPLEMENTING IGameWorldListener ////////////////////

void Asteroids::OnObjectRemoved(GameWorld* world, SmartPtr<GameObject> object)
{
    if (object->GetType() == GameObjectType("Asteroid"))
    {
        SmartPtr<GameObject> explosion = CreateExplosion();
        explosion->SetPosition(object->GetPosition());
        explosion->SetRotation(object->GetRotation());
        mGameWorld->AddObject(explosion);

        mAsteroidCount--;

        if(object->GetScale() > 0.2) {
            float newVel[4][2] = { {-1.0,-1.0}, { 1.0,-1.0},
                                   { 1.0, 1.0}, {-1.0, 1.0} };
            GLVector3f obPos = object->GetPosition();

            for(int i = 0; i < 4; i++)
            {
                SmartPtr<GameObject> newAsteroid = CreateAsteroid(obPos.x, obPos.y);
                float f = 5;    //force
                newAsteroid->SetVelocity(GLVector3f(newVel[i][0] * f + (rand() % 4), newVel[i][1] * f + (rand() % 4), 0.0));
                newAsteroid->SetScale(object->GetScale()/2);
                mGameWorld->AddObject(newAsteroid);
                mAsteroidCount++;
            }
        }

        if (mAsteroidCount <= 0)
        {
            SetTimer(500, START_NEXT_LEVEL);
        }
    }
    if (object->GetType() == GameObjectType("AsteroidOre"))
    {
        SmartPtr<GameObject> explosion = CreateExplosion();
        explosion->SetPosition(object->GetPosition());
        explosion->SetRotation(object->GetRotation());
        mGameWorld->AddObject(explosion);

        float newPos[4][2] = { {-1.0,-1.0}, { 1.0,-1.0},
                               { 1.0, 1.0}, {-1.0, 1.0} };
        GLVector3f obPos = object->GetPosition();
        float obRot = object->GetRotation();
        int sep = 5; // how much to separate the ore fromt he position of the asteroid

        for(int i = 0; i < 4; i++)
        {
            SmartPtr<GameObject> ore = CreateOre();
            ore->SetPosition(GLVector3f(obPos.x + newPos[i][0] * sep + (rand() % 4), obPos.y + newPos[i][1] * sep + (rand() % 4), 0.0));
            ore->SetRotation(obRot);
            mGameWorld->AddObject(ore);
        }

        int noA = 1 + (rand() % 3);
        cout << "RAND A: " << noA << endl;

        for (int i = 0; i < noA; i++)
        {
            SmartPtr<GameObject> newAsteroid = CreateAsteroid(obPos.x, obPos.y);
            float rA = rand() % 360; // a random angle
            cout << "RAND ANGLE: " << rA << endl;
            newAsteroid->SetVelocity(GLVector3f( cos(DEG2RAD * rA), sin(DEG2RAD * rA), 0.0));
            cout << "Object Scale: " << object->GetScale() << endl;
            newAsteroid->SetScale(object->GetScale());
            mGameWorld->AddObject(newAsteroid);
            mAsteroidCount++;
        }
    }
}

// PUBLIC INSTANCE METHODS IMPLEMENTING ITimerListener ////////////////////////

void Asteroids::OnTimer(int value)
{
    if (value == SHOW_GAME_OVER)
    {
        mGameOverLabel->SetVisible(true);
    }

    if (value == START_NEXT_LEVEL)
    {
        mLevel++;
        int num_asteroids = 10 + 2 * mLevel;
        for (int i = 0; i < num_asteroids; i++)
        {
            mGameWorld->AddObject(CreateAsteroid());
            mAsteroidCount++;
        }
    }

    if (value == CREATE_NEW_PLAYER)
    {
        mSpaceship->Reset();
        mGameWorld->AddObject(static_cast< SmartPtr<GameObject> >( mSpaceship ));
    }
}

// PROTECTED INSTANCE METHODS /////////////////////////////////////////////////

void Asteroids::CreateGUI()
{
    // Add a (transparent) border around the edge of the game display (offsets everything)
    mGameDisplay->GetContainer()->SetBorder(GLVector2i(0, 0));

    // Create a new GUILabel and wrap it up in a SmartPtr
    mScoreLabel = SmartPtr<GUILabel>(new GUILabel("Resources: 0"));
    // Set the vertical alignment of the label to GUI_VALIGN_TOP
    mScoreLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_TOP);
    // Add the GUILabel to the GUIComponent
    SmartPtr<GUIComponent> score_component = static_cast< SmartPtr<GUIComponent> >( mScoreLabel );
    mGameDisplay->GetContainer()->AddComponent(score_component, GLVector2f(0.0f, 1.0f));

    // Create a new GUILabel and wrap it up in a SmartPtr
    mLivesLabel = SmartPtr<GUILabel>(new GUILabel("Lives: 3"));
    // Set the vertical alignment of the label to GUI_VALIGN_BOTTOM
    mLivesLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_BOTTOM);
    // Add the GUILabel to the GUIComponent
    SmartPtr<GUIComponent> lives_component = static_cast< SmartPtr<GUIComponent> >( mLivesLabel );
    mGameDisplay->GetContainer()->AddComponent(lives_component, GLVector2f(0.0f, 0.0f));

    // Create a new GUILabel and wrap it up in a SmartPtr
    mGameOverLabel = SmartPtr<GUILabel>(new GUILabel("GAME OVER"));
    // Set the horizontal alignment of the label to GUI_HALIGN_CENTER
    mGameOverLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
    // Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
    mGameOverLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);
    // Set the visibility of the label to false (hidden)
    mGameOverLabel->SetVisible(false);
    // Add the GUILabel to the GUIContainer
    SmartPtr<GUIComponent> game_over_component = static_cast< SmartPtr<GUIComponent> >( mGameOverLabel );
    mGameDisplay->GetContainer()->AddComponent(game_over_component, GLVector2f(0.5f, 0.5f));

    // Create a new selection box
    mSelectionBox = SmartPtr<GUISelectionBox>(new GUISelectionBox());
    mSelectionBox->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_LEFT);
    mSelectionBox->SetVerticalAlignment(GUIComponent::GUI_VALIGN_TOP);
    // Let the selection box know how big is the display
    mSelectionBox->GiveDisplayDimensions(mGameDisplay->GetWidth(), mGameDisplay->GetHeight());
    // Add the GUISelectionBox to the GUIContainer
    SmartPtr<GUIComponent> selection_box = static_cast< SmartPtr<GUIComponent> >( mSelectionBox );
    mGameDisplay->GetContainer()->AddComponent(selection_box, GLVector2f(0.0f, 0.0f));
}

SmartPtr<GameObject> Asteroids::CreateSpaceship()
{
    // Create a raw pointer to a spaceship that can be converted to
    // SmartPtrs of different types because GameWorld implements IRefCount
    mSpaceship = SmartPtr<Spaceship>(new Spaceship());
    SmartPtr<Shape> spaceship_shape = new Shape("ASSETS/spaceship.shape");
    SmartPtr<Shape> thruster_shape = new Shape("ASSETS/thruster.shape");
    SmartPtr<Shape> bullet_shape = new Shape("ASSETS/bullet.shape");
    mSpaceship->SetSpaceshipShape(spaceship_shape);
    mSpaceship->SetThrusterShape(thruster_shape);
    mSpaceship->SetBulletShape(bullet_shape);
    Animation *anim_ptr = AnimationManager::GetInstance().GetAnimationByName("spaceship");
    SmartPtr<Sprite> spaceship_sprite = new Sprite(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
    mSpaceship->SetSprite(spaceship_sprite);
    mSpaceship->SetScale(0.1f);
    // Reset spaceship back to centre of the world
    mSpaceship->Reset();
    // Add the spaceship to the world
    SmartPtr<GameObject> object = static_cast< SmartPtr<GameObject> >( mSpaceship );

    //debug
    if(mConsoleDebug == true) cout << "Created the spaceship: " << mSpaceship->GetPosition().x << "," << mSpaceship->GetPosition().y << endl;

    return object;
}

SmartPtr<GameObject> Asteroids::CreateAsteroid()
{
    Animation *anim_ptr = AnimationManager::GetInstance().GetAnimationByName("asteroid1");
    SmartPtr<Sprite> asteroid_sprite = new Sprite(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
    asteroid_sprite->SetLoopAnimation(true);
    SmartPtr<GameObject> asteroid = new Asteroid();
    asteroid->SetSprite(asteroid_sprite);
    asteroid->SetScale(0.2f);

    //debug
    if(mConsoleDebug == true) cout << "Created the asteroid: " << asteroid->GetPosition().x << "," << asteroid->GetPosition().y << endl;

    return asteroid;
}


SmartPtr<GameObject> Asteroids::CreateAsteroid(int _x, int _y)
{
    SmartPtr<Shape> asteroid_shape = new Shape("ASSETS/asteroid.shape");
    Animation *anim_ptr = AnimationManager::GetInstance().GetAnimationByName("asteroid1");
    SmartPtr<Sprite> asteroid_sprite = new Sprite(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
    asteroid_sprite->SetLoopAnimation(true);
    SmartPtr<GameObject> asteroid = new Asteroid(_x, _y);
    asteroid->SetSprite(asteroid_sprite);
    asteroid->SetShape(asteroid_shape);
    asteroid->SetScale(0.2f);

    //debug
    if(mConsoleDebug == true) cout << "Created an asteroid: " << asteroid->GetPosition().x << "," << asteroid->GetPosition().y << endl;

    return asteroid;
}

SmartPtr<GameObject> Asteroids::CreateAsteroidOre(int _x, int _y)
{
    Animation *anim_ptr = AnimationManager::GetInstance().GetAnimationByName("asteroidOre1");
    SmartPtr<Sprite> asteroidOre_sprite = new Sprite(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
    asteroidOre_sprite->SetLoopAnimation(true);
    SmartPtr<GameObject> asteroidOre = new AsteroidOre(_x, _y);
    asteroidOre->SetSprite(asteroidOre_sprite);
    asteroidOre->SetScale(0.2f);

    //debug
    if(mConsoleDebug == true) cout << "Created an Ore asteroid: " << asteroidOre->GetPosition().x << "," << asteroidOre->GetPosition().y << endl;

    return asteroidOre;
}

SmartPtr<GameObject> Asteroids::CreateOre()
{
//    Animation *anim_ptr = AnimationManager::GetInstance().GetAnimationByName("asteroid1Ore");
//    SmartPtr<Sprite> asteroid_sprite = new Sprite(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
//    asteroid_sprite->SetLoopAnimation(true);
    SmartPtr<Shape> ore_shape = new Shape("ASSETS/ore.shape");
    SmartPtr<GameObject> ore = new Ore();
//    asteroidOre->SetSprite(asteroid_sprite);
    ore->SetShape(ore_shape);
    ore->SetScale(0.8f);

    return ore;
}

SmartPtr<GameObject> Asteroids::CreateOre(int _x, int _y)
{
//    Animation *anim_ptr = AnimationManager::GetInstance().GetAnimationByName("asteroid1Ore");
//    SmartPtr<Sprite> asteroid_sprite = new Sprite(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
//    asteroid_sprite->SetLoopAnimation(true);
    SmartPtr<Shape> ore_shape = new Shape("ASSETS/ore.shape");
    SmartPtr<GameObject> ore = new Ore(_x, _y);
//    asteroidOre->SetSprite(asteroid_sprite);
    ore->SetShape(ore_shape);
    ore->SetScale(0.8f);

    return ore;
}

SmartPtr<GameObject> Asteroids::CreateDrone(int _x, int _y)
{
   // SmartPtr<Drone> drone;

 //   drone = SmartPtr<Drone>(new Drone());
    SmartPtr<GameObject> drone = new Drone(_x, _y);

    SmartPtr<Shape> drone_shape = new Shape("ASSETS/drone.shape");
    SmartPtr<Shape> bullet_shape = new Shape("ASSETS/bullet.shape");

    drone->SetShape(drone_shape);
    drone->SetSelectedShape(mSelectedShape);
   // drone->SetBulletShape(bullet_shape);
    //drone->SetSprite(drone_sprite);
    drone->SetScale(1.0f);

    SmartPtr<GameObject> object = static_cast< SmartPtr<GameObject> >( drone );

    return drone;

    ///////////////////////
//    SmartPtr<Shape> drone_shape = new Shape("ASSETS/drone.shape");
//    SmartPtr<Shape> bullet_shape = new Shape("ASSETS/bullet.shape");
//
//    SmartPtr<Drone> drone;
//    drone = SmartPtr<Drone>(new Drone(_x, _y));
//
//    drone->SetShape(drone_shape);
//    drone->SetSelectedShape(mSelectedShape);
//    drone->SetBulletShape(bullet_shape);
//
//    SmartPtr<GameObject> object = static_cast< SmartPtr<GameObject> >( drone );
//    //drone->SetSprite(drone_sprite);
//
//    drone->SetScale(1.0f);
//    return drone;
}
//
//SmartPtr<GameObject> Asteroids::ProduceDrone(int _x, int _y)
//{
//    GLVector3f spaceship_pos = mSpaceship->GetPosition();
//    float angle = rand() % 360;
//    SmartPtr<GameObject> drone = CreateDrone();
//    return drone;
//}

SmartPtr<GameObject> Asteroids::CreateExplosion()
{
    Animation *anim_ptr = AnimationManager::GetInstance().GetAnimationByName("explosion");
    SmartPtr<Sprite> explosion_sprite = new Sprite(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
    explosion_sprite->SetLoopAnimation(false);
    SmartPtr<GameObject> explosion = new Explosion();
    explosion->SetSprite(explosion_sprite);
    explosion->Reset();
    return explosion;
}

