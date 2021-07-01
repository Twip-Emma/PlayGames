using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class 角色移动 : MonoBehaviour
{

    public float speed = 7f;//设置速度
    Rigidbody2D rbody;
    private int maxHealth = 10;//最大生命
    private int currentHealth;//当前生命值

    public int MyMaxHealth {get{return maxHealth;}}
    public int MyCurrentHealth {get{return currentHealth;}}

    //================无敌相关=================
    private float superTime = 2f;//设置无敌时间
    private float superTimeStart;
    private bool superTimeCheck;

    //================动画相关=================
    private Vector2 lookDirection = new Vector2(1, 0);//默认朝右
    Animator anim;

    //================子弹相关=================
    public GameObject bulletPrefab;//子弹
    [SerializeField] //序列化
    private int maxBulletCount = 99;//最大子弹
    private int curBulletCount;//当前子弹

    public int MyCurBulletCount{get{return curBulletCount;}}
    public int MyMaxBulletCount{get{return maxBulletCount;}}

    //================玩家音效=================
    public AudioClip hitClip;
    public AudioClip LaunchClip;

    // Start is called before the first frame update
    void Start()
    {
        superTimeStart = 0;
        currentHealth = 10;
        curBulletCount = 15;
        rbody = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
        UImanager.instance.UpdateHealthBar(currentHealth, maxHealth);
    }

    // Update is called once per frame
    void Update()
    {

        //==============角色移动控制===================
		float moveX = Input.GetAxisRaw("Horizontal");
 	   	float moveY = Input.GetAxisRaw("Vertical");

        //==============角色动画设置===================
        Vector2 moveVector = new Vector2(moveX, moveY);
        if(moveVector.x != 0 || moveVector.y != 0){
            lookDirection = moveVector;
        }//静止时锁定玩家朝向
        anim.SetFloat("Look X", lookDirection.x);
        anim.SetFloat("Look Y", lookDirection.y);
        anim.SetFloat("Speed", moveVector.magnitude);

		Vector2 position = rbody.position;
		// position.x += moveX * speed * Time.deltaTime;
		// position.y += moveY * speed * Time.deltaTime;
        position += moveVector * speed * Time.deltaTime;//第二种移动的写法
		// transform.position = position;
        rbody.MovePosition(position);
        // transform.Translate(transform.right*speed*Time.deltaTime);

        //==============无敌时间====================
        if(superTimeCheck){
            superTimeStart -= Time.deltaTime;
            if(superTimeStart < 0){
                superTimeCheck = false;//取消无敌状态
            }
        }

        //=============按下J键，且子弹大于0，进行攻击==================
        if(Input.GetKeyDown(KeyCode.J) && curBulletCount > 0){
            ChangeBulletCount(-1);//攻击-1子弹
            anim.SetTrigger("Launch");//播放攻击动画
            AudioManager.instance.AudioPlay(LaunchClip);//攻击音效
            GameObject bullet = Instantiate(bulletPrefab, rbody.position + Vector2.up * 0.5f, Quaternion.identity);
            子弹控制 bc = bullet.GetComponent<子弹控制>();
            if(bc != null){
                bc.Move(lookDirection,300);
            }
        }

        //=============按下E键 与NPC交互==========
        if(Input.GetKeyDown(KeyCode.E)){
            RaycastHit2D hit = Physics2D.Raycast(rbody.position,lookDirection,2f,LayerMask.GetMask("NPC"));
            if(hit.collider != null){
                Debug.Log("玩家与NPC交互");
                NPCmanager npc = hit.collider.GetComponent<NPCmanager>();
                if(npc != null){
                    npc.ShowDialog();//显示对话框
                }
            }
        }
    }

    //改变生命值
    public void ChangeHealth(int amount){
        //判断玩家受否收到伤害
        if(amount < 0){
            if(superTimeCheck == true){
                return;
            }
            superTimeCheck = true;
            AudioManager.instance.AudioPlay(hitClip);//受伤音效
            superTimeStart = superTime;
        }

        //约束生命加减
        Debug.Log(currentHealth + "/" + maxHealth);
        currentHealth = Mathf.Clamp(currentHealth + amount, 0, maxHealth);
        // UImanager UImanager;
        
        UImanager.instance.UpdateHealthBar(currentHealth, maxHealth);

        Debug.Log(currentHealth + "/" + maxHealth);
    }

    public void ChangeBulletCount(int amount){
        curBulletCount = Mathf.Clamp(curBulletCount + amount, 0, maxBulletCount);
        UImanager.instance.UpdateBulletCount(curBulletCount, maxBulletCount);
    }
}
